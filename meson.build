project('pcl', [ 'c', 'cpp' ],
        default_options : ['c_std=c11', 'cpp_std=c++14'],
        license: 'BSD')

version = '1.8.1'
dev_version = true

compiler = meson.get_compiler('cpp')

have_mm_malloc = compiler.compiles('''
#include <mm_malloc.h>
int main()
{
    void* mem = _mm_malloc (100, 16);
    return 0;
}
''', name: 'Have MM Malloc')

have_posix_memalign = compiler.compiles('''
#include <stdlib.h>
int main()
{
  void* mem;
  return posix_memalign (&mem, 16, 100);
}
''', name: 'Have Posix Memalign')

have_sse4_2 = compiler.compiles('''
#include <emmintrin.h>
#include <nmmintrin.h>
int main ()
{
  long long a[2] = {  1, 2 };
  long long b[2] = { -1, 3 };
  long long c[2];
  __m128i va = _mm_loadu_si128 ((__m128i*)a);
  __m128i vb = _mm_loadu_si128 ((__m128i*)b);
  __m128i vc = _mm_cmpgt_epi64 (va, vb);

  _mm_storeu_si128 ((__m128i*)c, vc);
  if (c[0] == -1LL && c[1] == 0LL)
    return (0);
  else
    return (1);
}
''', name: 'Have SSE 4.2 Extensions')

have_sse4_1 = compiler.compiles('''
#include <smmintrin.h>
int main ()
{
  __m128 a, b;
  float vals[4] = {1, 2, 3, 4};
  const int mask = 123;
  a = _mm_loadu_ps (vals);
  b = a;
  b = _mm_dp_ps (a, a, mask);
  _mm_storeu_ps (vals,b);
  return (0);
}
''', name: 'Have SSE 4.1 Extensions')

have_ssse3 = compiler.compiles('''
#include <tmmintrin.h>
int main ()
{
  __m128i a, b;
  int vals[4] = {-1, -2, -3, -4};
  a = _mm_loadu_si128 ((const __m128i*)vals);
  b = _mm_abs_epi32 (a);
  _mm_storeu_si128 ((__m128i*)vals, b);
  return (0);
}
''', name: 'Have SSSE 3 Extensions')

have_sse3 = compiler.compiles('''
#include <pmmintrin.h>
int main ()
{
    __m128d a, b;
    double vals[2] = {0};
    a = _mm_loadu_pd (vals);
    b = _mm_hadd_pd (a,a);
    _mm_storeu_pd (vals, b);
    return (0);
}
''', name: 'Have SSE 3 Extensions')

have_sse2 = compiler.compiles('''
#include <emmintrin.h>
int main ()
{
    __m128d a, b;
    double vals[2] = {0};
    a = _mm_loadu_pd (vals);
    b = _mm_add_pd (a,a);
    _mm_storeu_pd (vals,b);
    return (0);
}
''', name: 'Have SSE 2 Extensions')

have_sse = compiler.compiles('''
#include <xmmintrin.h>
int main ()
{
    __m128 a, b;
    float vals[4] = {0};
    a = _mm_loadu_ps (vals);
    b = a;
    b = _mm_add_ps (a,b);
    _mm_storeu_ps (vals,b);
    return (0);
}
''', name: 'Have SSE Extensions')

subdir('pcl')

threads_dep = dependency('threads')
m_dep = compiler.find_library('m', required : false)
eigen_dep = dependency('eigen3', fallback: [ 'eigen3', 'eigen_dep' ])
flann_dep = dependency('flann', fallback: [ 'flann', 'cpp_dep' ])

boost_system_dep = dependency('boost', modules: [ 'system' ], fallback: [ 'boost', 'system_dep' ])
boost_thread_dep = dependency('boost', modules: [ 'thread' ], fallback: [ 'boost', 'thread_dep' ])
boost_deps = [ boost_system_dep, boost_thread_dep ]


common_inc = include_directories('.', 'common/include')
common_defines = []
common_src = [
    'common/src/bearing_angle_image.cpp',
    'common/src/range_image.cpp',
    'common/src/range_image_planar.cpp',

    'common/src/point_types.cpp',
    'common/src/pcl_base.cpp',
    'common/src/io.cpp',
    'common/src/common.cpp',
    'common/src/correspondence.cpp',
    'common/src/distances.cpp',
    'common/src/parse.cpp',
    'common/src/poses_from_matches.cpp',
    'common/src/print.cpp',
    'common/src/projection_matrix.cpp',
    'common/src/time_trigger.cpp',
    'common/src/gaussian.cpp',
    'common/src/colors.cpp',
    'common/src/feature_histogram.cpp',

    'common/src/fft/kiss_fft.c',
    'common/src/fft/kiss_fftr.c',
]
common_deps = [ threads_dep, m_dep ]
common_deps += eigen_dep

common_deps += boost_deps

common_lib = shared_library('pcl_common', common_src,
        version: version,
        cpp_args: common_defines,
        include_directories: common_inc,
        dependencies: common_deps)
common_dep = declare_dependency(link_with: common_lib,
        include_directories: common_inc,
        dependencies: common_deps)

octree_inc = include_directories('.', 'octree/include')
octree_defines = []
octree_src = [
    'octree/src/octree_inst.cpp'
]
octree_deps = [ threads_dep, m_dep, common_dep ]
octree_deps += eigen_dep

octree_lib = shared_library('pcl_octree', octree_src,
        version: version,
        cpp_args: octree_defines,
        include_directories: [common_inc, octree_inc],
        dependencies: octree_deps)
octree_dep = declare_dependency(link_with: octree_lib,
        include_directories: [common_inc, octree_inc],
        dependencies: octree_deps)

kdtree_inc = include_directories('.', 'kdtree/include')
kdtree_defines = []
kdtree_src = [
    'kdtree/src/kdtree_flann.cpp'
]
kdtree_deps = [ threads_dep, m_dep, flann_dep, eigen_dep, common_dep ]

kdtree_lib = shared_library('pcl_kdtree', kdtree_src,
        version: version,
        cpp_args: kdtree_defines,
        include_directories: [common_inc, kdtree_inc],
        dependencies: kdtree_deps)
kdtree_dep = declare_dependency(link_with: kdtree_lib,
        include_directories: [common_inc, kdtree_inc],
        dependencies: kdtree_deps)

search_inc = include_directories('.', 'search/include')
search_defines = []
search_src = [
    'search/src/search.cpp',
    'search/src/kdtree.cpp',
    'search/src/brute_force.cpp',
    'search/src/organized.cpp',
    'search/src/octree.cpp',
]
search_deps = [ threads_dep, m_dep, common_dep, kdtree_dep, octree_dep ]

search_lib = shared_library('pcl_search', search_src,
        version: version,
        cpp_args: search_defines,
        include_directories: [common_inc, octree_inc, kdtree_inc, search_inc],
        dependencies: search_deps)
search_dep = declare_dependency(link_with: search_lib,
        include_directories: [common_inc, octree_inc, kdtree_inc, search_inc],
        dependencies: search_deps)

sample_consensus_inc = include_directories('.', 'sample_consensus/include')
sample_consensus_defines = []
sample_consensus_src = [
    'sample_consensus/src/sac.cpp',
    'sample_consensus/src/sac_model_circle.cpp',
    'sample_consensus/src/sac_model_circle3d.cpp',
    'sample_consensus/src/sac_model_cylinder.cpp',
    'sample_consensus/src/sac_model_cone.cpp',
    'sample_consensus/src/sac_model_line.cpp',
    'sample_consensus/src/sac_model_parallel_line.cpp',
    'sample_consensus/src/sac_model_stick.cpp',
    'sample_consensus/src/sac_model_normal_parallel_plane.cpp',
    'sample_consensus/src/sac_model_normal_plane.cpp',
    'sample_consensus/src/sac_model_normal_sphere.cpp',
    'sample_consensus/src/sac_model_plane.cpp',
    'sample_consensus/src/sac_model_registration.cpp',
    'sample_consensus/src/sac_model_sphere.cpp',
]
sample_consensus_deps = [ common_dep, search_dep ]

sample_consensus_lib = shared_library('pcl_sample_consensus', sample_consensus_src,
        version: version,
        cpp_args: sample_consensus_defines,
        include_directories: [common_inc, octree_inc, kdtree_inc, sample_consensus_inc],
        dependencies: sample_consensus_deps)
sample_consensus_dep = declare_dependency(link_with: sample_consensus_lib,
        include_directories: [common_inc, octree_inc, kdtree_inc, sample_consensus_inc],
        dependencies: sample_consensus_deps)

filters_inc = include_directories('.', 'filters/include')
filters_defines = []
filters_src = [
    'filters/src/conditional_removal.cpp',
    'filters/src/crop_box.cpp',
    'filters/src/extract_indices.cpp',
    'filters/src/filter.cpp',
    'filters/src/filter_indices.cpp',
    'filters/src/passthrough.cpp',
    'filters/src/shadowpoints.cpp',
    'filters/src/project_inliers.cpp',
    'filters/src/radius_outlier_removal.cpp',
    'filters/src/random_sample.cpp',
    'filters/src/normal_space.cpp',
    'filters/src/sampling_surface_normal.cpp',
    'filters/src/statistical_outlier_removal.cpp',
    'filters/src/voxel_grid.cpp',
    'filters/src/approximate_voxel_grid.cpp',
    'filters/src/bilateral.cpp',
    'filters/src/fast_bilateral.cpp',
    'filters/src/fast_bilateral_omp.cpp',
    'filters/src/crop_hull.cpp',
    'filters/src/voxel_grid_covariance.cpp',
    'filters/src/voxel_grid_label.cpp',
    'filters/src/frustum_culling.cpp',
    'filters/src/covariance_sampling.cpp',
    'filters/src/median_filter.cpp',
    'filters/src/uniform_sampling.cpp',
    'filters/src/voxel_grid_occlusion_estimation.cpp',
    'filters/src/normal_refinement.cpp',
    'filters/src/grid_minimum.cpp',
    'filters/src/morphological_filter.cpp',
    'filters/src/local_maximum.cpp',
    'filters/src/model_outlier_removal.cpp',
]
filters_deps = [
    common_dep,
    kdtree_dep,
    octree_dep,
    search_dep,
    sample_consensus_dep,
]

filters_lib = shared_library('pcl_filters', filters_src,
        version: version,
        cpp_args: filters_defines,
        include_directories: [common_inc, octree_inc, kdtree_inc, filters_inc],
        dependencies: filters_deps)
filters_dep = declare_dependency(link_with: filters_lib,
        include_directories: [common_inc, octree_inc, kdtree_inc, filters_inc],
        dependencies: filters_deps)

features_inc = include_directories('.', 'features/include', '2d/include')
features_defines = []
features_src = [
    'features/src/board.cpp',
    'features/src/brisk_2d.cpp',
    'features/src/boundary.cpp',
    'features/src/cppf.cpp',
    'features/src/cvfh.cpp',
    'features/src/our_cvfh.cpp',
    'features/src/crh.cpp',
    'features/src/don.cpp',
    'features/src/fpfh.cpp',
    'features/src/gfpfh.cpp',
    'features/src/integral_image_normal.cpp',
    'features/src/intensity_gradient.cpp',
    'features/src/intensity_spin.cpp',
    'features/src/linear_least_squares_normal.cpp',
    'features/src/moment_invariants.cpp',
    'features/src/moment_of_inertia_estimation.cpp',
    'features/src/multiscale_feature_persistence.cpp',
    'features/src/narf.cpp',
    'features/src/normal_3d.cpp',
    'features/src/normal_based_signature.cpp',
    'features/src/organized_edge_detection.cpp',
    'features/src/pfh.cpp',
    'features/src/ppf.cpp',
    'features/src/shot.cpp',
    'features/src/shot_lrf.cpp',
    'features/src/spin_image.cpp',
    'features/src/principal_curvatures.cpp',
    'features/src/rift.cpp',
    'features/src/rops_estimation.cpp',
    'features/src/rsd.cpp',
    'features/src/grsd.cpp',
    'features/src/statistical_multiscale_interest_region_extraction.cpp',
    'features/src/vfh.cpp',
    'features/src/esf.cpp',
    'features/src/3dsc.cpp',
    'features/src/usc.cpp',
    'features/src/range_image_border_extractor.cpp',
]
features_deps = [
    common_dep,
    kdtree_dep,
    octree_dep,
    search_dep,
    sample_consensus_dep,
    filters_dep,
]

features_lib = shared_library('pcl_features', features_src,
        version: version,
        cpp_args: features_defines,
        include_directories: [common_inc, octree_inc, kdtree_inc, features_inc],
        dependencies: features_deps)
features_dep = declare_dependency(link_with: features_lib,
        include_directories: [common_inc, octree_inc, kdtree_inc, features_inc],
        dependencies: features_deps)


ml_inc = include_directories('.', 'ml/include')
ml_defines = []
ml_src = [
    'ml/src/point_xy_32i.cpp',
    'ml/src/point_xy_32f.cpp',
    'ml/src/densecrf.cpp',
    'ml/src/pairwise_potential.cpp',
    'ml/src/permutohedral.cpp',
#    'ml/src/permutohedralORI.cpp',
#    'ml/src/filter.cpp',
#    'ml/src/util.cpp',
#    'ml/src/densecrfORI.cpp		',
    'ml/src/svm_wrapper.cpp',
    'ml/src/svm.cpp',
    'ml/src/kmeans.cpp',
]
ml_deps = [ common_dep ]

ml_lib = shared_library('pcl_ml', ml_src,
        version: version,
        cpp_args: ml_defines,
        include_directories: [common_inc, octree_inc, kdtree_inc, ml_inc],
        dependencies: ml_deps)
ml_dep = declare_dependency(link_with: ml_lib,
        include_directories: [common_inc, octree_inc, kdtree_inc, ml_inc],
        dependencies: ml_deps)


segmentation_inc = include_directories('.', 'segmentation/include', 'geometry/include')
segmentation_defines = []
segmentation_src = [
    'segmentation/src/extract_clusters.cpp',
    'segmentation/src/extract_polygonal_prism_data.cpp',
    'segmentation/src/sac_segmentation.cpp',
    'segmentation/src/seeded_hue_segmentation.cpp',
    'segmentation/src/segment_differences.cpp',
    'segmentation/src/region_growing.cpp',
    'segmentation/src/region_growing_rgb.cpp',
    'segmentation/src/organized_connected_component_segmentation.cpp',
    'segmentation/src/organized_multi_plane_segmentation.cpp',
    'segmentation/src/planar_polygon_fusion.cpp',
    'segmentation/src/crf_segmentation.cpp',
    'segmentation/src/crf_normal_segmentation.cpp',
    'segmentation/src/unary_classifier.cpp',
    'segmentation/src/conditional_euclidean_clustering.cpp',
    'segmentation/src/supervoxel_clustering.cpp',
    'segmentation/src/grabcut_segmentation.cpp',
    'segmentation/src/progressive_morphological_filter.cpp',
    'segmentation/src/approximate_progressive_morphological_filter.cpp',
    'segmentation/src/lccp_segmentation.cpp',
    'segmentation/src/cpc_segmentation.cpp',
]
segmentation_deps = [
    common_dep,
    kdtree_dep,
    octree_dep,
    search_dep,
    sample_consensus_dep,
    filters_dep,
    features_dep,
    ml_dep,
]

segmentation_lib = shared_library('pcl_segmentation', segmentation_src,
        version: version,
        cpp_args: segmentation_defines,
        include_directories: [common_inc, octree_inc, kdtree_inc, segmentation_inc],
        dependencies: segmentation_deps)
segmentation_dep = declare_dependency(link_with: segmentation_lib,
        include_directories: [common_inc, octree_inc, kdtree_inc, segmentation_inc],
        dependencies: segmentation_deps)



