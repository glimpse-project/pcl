/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2010-2012, Willow Garage, Inc.
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  $Id$
 */

#include <pcl/io/pcd_io.h>
#include <pcl/console/print.h>

#include <pcl/outofcore/outofcore.h>
#include <pcl/outofcore/outofcore_impl.h>

#include <pcl/outofcore/OutofcoreIteratorBase.h>

#include <pcl/outofcore/OutofcoreDepthFirstIterator.h>
#include <pcl/outofcore/impl/OutofcoreDepthFirstIterator.hpp>

using namespace pcl::outofcore;

typedef OutofcoreOctreeBase<OutofcoreOctreeDiskContainer<pcl::PointXYZ>, pcl::PointXYZ> OctreeDisk;
typedef OutofcoreOctreeBaseNode<OutofcoreOctreeDiskContainer<pcl::PointXY>, pcl::PointXYZ> OctreeDiskNode;

int main (int argc, char** argv)
{
//  pcl::console::setVerbosityLevel (pcl::console::L_VERBOSE);

  int depth = 3;
  Eigen::Vector3d min (-10.0, -10.0, -10.0);
  Eigen::Vector3d max (10.0, 10.0, 10.0);
  boost::filesystem::path file_location ("tree/tree.oct_idx");
  
  OctreeDisk* octree;
  
  octree = new OctreeDisk (depth, min, max, file_location, "ECEF");

  sensor_msgs::PointCloud2::Ptr cloud (new sensor_msgs::PointCloud2 ());
    
  pcl::io::loadPCDFile (argv[1], *cloud);

  octree->addPointCloud (cloud, false);

  pcl::io::loadPCDFile (argv[2], *cloud);
  octree->addPointCloud (cloud, false);
  
  octree->buildLOD ();
  
  delete octree;

  OctreeDisk octree2 (file_location, true);

  //iterate over the octree, depth first
  OutofcoreDepthFirstIterator<pcl::PointXYZ, pcl::outofcore::OutofcoreOctreeDiskContainer<pcl::PointXYZ> > it (octree2);
  OctreeDisk::Iterator myit (octree2);

  while ( *myit !=0 )
  {
    octree2.printBoundingBox (**myit);
    myit++;
  }

  return (0);
}