
conf_data = configuration_data()

version_pretty = version
if dev_version
    version_pretty += '-dev'
endif
conf_data.set('version', version)
conf_data.set('pcl_major_version', version.split('.').get(0))
conf_data.set('pcl_minor_version', version.split('.').get(1))
conf_data.set('pcl_revision_version', version.split('.').get(2))
conf_data.set('pcl_dev_version', dev_version ? 1 : 0)
conf_data.set('pcl_version_pretty', version_pretty)
conf_data.set('pcl_version_string', '"' + version + '"')
conf_data.set('buildtype', get_option('buildtype'))

conf_data.set('HAVE_MM_MALLOC', have_mm_malloc)
conf_data.set('HAVE_POSIX_MEMALIGN', have_posix_memalign)
conf_data.set('HAVE_SSE4_2_EXTENSIONS', have_sse4_2)
conf_data.set('HAVE_SSE4_1_EXTENSIONS', have_sse4_1)
conf_data.set('HAVE_SSSE3_EXTENSIONS', have_ssse3)
conf_data.set('HAVE_SSE3_EXTENSIONS', have_sse3)
conf_data.set('HAVE_SSE2_EXTENSIONS', have_sse2)
conf_data.set('HAVE_SSE_EXTENSIONS', have_sse)

verbosity = get_option('verbosity_level').to_upper()
conf_data.set('verbosity_level', verbosity)
configure_file(input : 'pcl_config.meson',
               output : 'pcl_config.h',
               configuration : conf_data)


