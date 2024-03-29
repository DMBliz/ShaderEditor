/*

    EGL loader generated by glad 0.1.16a0 on Thu Nov 16 22:12:55 2017.

    Language/Generator: C/C++
    Specification: egl
    APIs: egl=1.5
    Profile: -
    Extensions:
        EGL_ANDROID_blob_cache,
        EGL_ANDROID_create_native_client_buffer,
        EGL_ANDROID_framebuffer_target,
        EGL_ANDROID_front_buffer_auto_refresh,
        EGL_ANDROID_get_frame_timestamps,
        EGL_ANDROID_get_native_client_buffer,
        EGL_ANDROID_image_native_buffer,
        EGL_ANDROID_native_fence_sync,
        EGL_ANDROID_presentation_time,
        EGL_ANDROID_recordable,
        EGL_ANGLE_d3d_share_handle_client_buffer,
        EGL_ANGLE_device_d3d,
        EGL_ANGLE_query_surface_pointer,
        EGL_ANGLE_surface_d3d_texture_2d_share_handle,
        EGL_ANGLE_window_fixed_size,
        EGL_ARM_implicit_external_sync,
        EGL_ARM_pixmap_multisample_discard,
        EGL_EXT_bind_to_front,
        EGL_EXT_buffer_age,
        EGL_EXT_client_extensions,
        EGL_EXT_compositor,
        EGL_EXT_create_context_robustness,
        EGL_EXT_device_base,
        EGL_EXT_device_drm,
        EGL_EXT_device_enumeration,
        EGL_EXT_device_openwf,
        EGL_EXT_device_query,
        EGL_EXT_gl_colorspace_bt2020_linear,
        EGL_EXT_gl_colorspace_bt2020_pq,
        EGL_EXT_gl_colorspace_display_p3,
        EGL_EXT_gl_colorspace_display_p3_linear,
        EGL_EXT_gl_colorspace_scrgb,
        EGL_EXT_gl_colorspace_scrgb_linear,
        EGL_EXT_image_dma_buf_import,
        EGL_EXT_image_dma_buf_import_modifiers,
        EGL_EXT_image_implicit_sync_control,
        EGL_EXT_multiview_window,
        EGL_EXT_output_base,
        EGL_EXT_output_drm,
        EGL_EXT_output_openwf,
        EGL_EXT_pixel_format_float,
        EGL_EXT_platform_base,
        EGL_EXT_platform_device,
        EGL_EXT_platform_wayland,
        EGL_EXT_platform_x11,
        EGL_EXT_protected_content,
        EGL_EXT_protected_surface,
        EGL_EXT_stream_consumer_egloutput,
        EGL_EXT_surface_CTA861_3_metadata,
        EGL_EXT_surface_SMPTE2086_metadata,
        EGL_EXT_swap_buffers_with_damage,
        EGL_EXT_yuv_surface,
        EGL_HI_clientpixmap,
        EGL_HI_colorformats,
        EGL_IMG_context_priority,
        EGL_IMG_image_plane_attribs,
        EGL_KHR_cl_event,
        EGL_KHR_cl_event2,
        EGL_KHR_client_get_all_proc_addresses,
        EGL_KHR_config_attribs,
        EGL_KHR_context_flush_control,
        EGL_KHR_create_context,
        EGL_KHR_create_context_no_error,
        EGL_KHR_debug,
        EGL_KHR_display_reference,
        EGL_KHR_fence_sync,
        EGL_KHR_get_all_proc_addresses,
        EGL_KHR_gl_colorspace,
        EGL_KHR_gl_renderbuffer_image,
        EGL_KHR_gl_texture_2D_image,
        EGL_KHR_gl_texture_3D_image,
        EGL_KHR_gl_texture_cubemap_image,
        EGL_KHR_image,
        EGL_KHR_image_base,
        EGL_KHR_image_pixmap,
        EGL_KHR_lock_surface,
        EGL_KHR_lock_surface2,
        EGL_KHR_lock_surface3,
        EGL_KHR_mutable_render_buffer,
        EGL_KHR_no_config_context,
        EGL_KHR_partial_update,
        EGL_KHR_platform_android,
        EGL_KHR_platform_gbm,
        EGL_KHR_platform_wayland,
        EGL_KHR_platform_x11,
        EGL_KHR_reusable_sync,
        EGL_KHR_stream,
        EGL_KHR_stream_attrib,
        EGL_KHR_stream_consumer_gltexture,
        EGL_KHR_stream_cross_process_fd,
        EGL_KHR_stream_fifo,
        EGL_KHR_stream_producer_aldatalocator,
        EGL_KHR_stream_producer_eglsurface,
        EGL_KHR_surfaceless_context,
        EGL_KHR_swap_buffers_with_damage,
        EGL_KHR_vg_parent_image,
        EGL_KHR_wait_sync,
        EGL_MESA_drm_image,
        EGL_MESA_image_dma_buf_export,
        EGL_MESA_platform_gbm,
        EGL_MESA_platform_surfaceless,
        EGL_NOK_swap_region,
        EGL_NOK_swap_region2,
        EGL_NOK_texture_from_pixmap,
        EGL_NV_3dvision_surface,
        EGL_NV_coverage_sample,
        EGL_NV_coverage_sample_resolve,
        EGL_NV_cuda_event,
        EGL_NV_depth_nonlinear,
        EGL_NV_device_cuda,
        EGL_NV_native_query,
        EGL_NV_post_convert_rounding,
        EGL_NV_post_sub_buffer,
        EGL_NV_robustness_video_memory_purge,
        EGL_NV_stream_consumer_gltexture_yuv,
        EGL_NV_stream_cross_display,
        EGL_NV_stream_cross_object,
        EGL_NV_stream_cross_partition,
        EGL_NV_stream_cross_process,
        EGL_NV_stream_cross_system,
        EGL_NV_stream_fifo_next,
        EGL_NV_stream_fifo_synchronous,
        EGL_NV_stream_frame_limits,
        EGL_NV_stream_metadata,
        EGL_NV_stream_remote,
        EGL_NV_stream_reset,
        EGL_NV_stream_socket,
        EGL_NV_stream_socket_inet,
        EGL_NV_stream_socket_unix,
        EGL_NV_stream_sync,
        EGL_NV_sync,
        EGL_NV_system_time,
        EGL_TIZEN_image_native_buffer,
        EGL_TIZEN_image_native_surface
    Loader: True
    Local files: False
    Omit khrplatform: False

    Commandline:
        --api="egl=1.5" --generator="c" --spec="egl" --extensions="EGL_ANDROID_blob_cache,EGL_ANDROID_create_native_client_buffer,EGL_ANDROID_framebuffer_target,EGL_ANDROID_front_buffer_auto_refresh,EGL_ANDROID_get_frame_timestamps,EGL_ANDROID_get_native_client_buffer,EGL_ANDROID_image_native_buffer,EGL_ANDROID_native_fence_sync,EGL_ANDROID_presentation_time,EGL_ANDROID_recordable,EGL_ANGLE_d3d_share_handle_client_buffer,EGL_ANGLE_device_d3d,EGL_ANGLE_query_surface_pointer,EGL_ANGLE_surface_d3d_texture_2d_share_handle,EGL_ANGLE_window_fixed_size,EGL_ARM_implicit_external_sync,EGL_ARM_pixmap_multisample_discard,EGL_EXT_bind_to_front,EGL_EXT_buffer_age,EGL_EXT_client_extensions,EGL_EXT_compositor,EGL_EXT_create_context_robustness,EGL_EXT_device_base,EGL_EXT_device_drm,EGL_EXT_device_enumeration,EGL_EXT_device_openwf,EGL_EXT_device_query,EGL_EXT_gl_colorspace_bt2020_linear,EGL_EXT_gl_colorspace_bt2020_pq,EGL_EXT_gl_colorspace_display_p3,EGL_EXT_gl_colorspace_display_p3_linear,EGL_EXT_gl_colorspace_scrgb,EGL_EXT_gl_colorspace_scrgb_linear,EGL_EXT_image_dma_buf_import,EGL_EXT_image_dma_buf_import_modifiers,EGL_EXT_image_implicit_sync_control,EGL_EXT_multiview_window,EGL_EXT_output_base,EGL_EXT_output_drm,EGL_EXT_output_openwf,EGL_EXT_pixel_format_float,EGL_EXT_platform_base,EGL_EXT_platform_device,EGL_EXT_platform_wayland,EGL_EXT_platform_x11,EGL_EXT_protected_content,EGL_EXT_protected_surface,EGL_EXT_stream_consumer_egloutput,EGL_EXT_surface_CTA861_3_metadata,EGL_EXT_surface_SMPTE2086_metadata,EGL_EXT_swap_buffers_with_damage,EGL_EXT_yuv_surface,EGL_HI_clientpixmap,EGL_HI_colorformats,EGL_IMG_context_priority,EGL_IMG_image_plane_attribs,EGL_KHR_cl_event,EGL_KHR_cl_event2,EGL_KHR_client_get_all_proc_addresses,EGL_KHR_config_attribs,EGL_KHR_context_flush_control,EGL_KHR_create_context,EGL_KHR_create_context_no_error,EGL_KHR_debug,EGL_KHR_display_reference,EGL_KHR_fence_sync,EGL_KHR_get_all_proc_addresses,EGL_KHR_gl_colorspace,EGL_KHR_gl_renderbuffer_image,EGL_KHR_gl_texture_2D_image,EGL_KHR_gl_texture_3D_image,EGL_KHR_gl_texture_cubemap_image,EGL_KHR_image,EGL_KHR_image_base,EGL_KHR_image_pixmap,EGL_KHR_lock_surface,EGL_KHR_lock_surface2,EGL_KHR_lock_surface3,EGL_KHR_mutable_render_buffer,EGL_KHR_no_config_context,EGL_KHR_partial_update,EGL_KHR_platform_android,EGL_KHR_platform_gbm,EGL_KHR_platform_wayland,EGL_KHR_platform_x11,EGL_KHR_reusable_sync,EGL_KHR_stream,EGL_KHR_stream_attrib,EGL_KHR_stream_consumer_gltexture,EGL_KHR_stream_cross_process_fd,EGL_KHR_stream_fifo,EGL_KHR_stream_producer_aldatalocator,EGL_KHR_stream_producer_eglsurface,EGL_KHR_surfaceless_context,EGL_KHR_swap_buffers_with_damage,EGL_KHR_vg_parent_image,EGL_KHR_wait_sync,EGL_MESA_drm_image,EGL_MESA_image_dma_buf_export,EGL_MESA_platform_gbm,EGL_MESA_platform_surfaceless,EGL_NOK_swap_region,EGL_NOK_swap_region2,EGL_NOK_texture_from_pixmap,EGL_NV_3dvision_surface,EGL_NV_coverage_sample,EGL_NV_coverage_sample_resolve,EGL_NV_cuda_event,EGL_NV_depth_nonlinear,EGL_NV_device_cuda,EGL_NV_native_query,EGL_NV_post_convert_rounding,EGL_NV_post_sub_buffer,EGL_NV_robustness_video_memory_purge,EGL_NV_stream_consumer_gltexture_yuv,EGL_NV_stream_cross_display,EGL_NV_stream_cross_object,EGL_NV_stream_cross_partition,EGL_NV_stream_cross_process,EGL_NV_stream_cross_system,EGL_NV_stream_fifo_next,EGL_NV_stream_fifo_synchronous,EGL_NV_stream_frame_limits,EGL_NV_stream_metadata,EGL_NV_stream_remote,EGL_NV_stream_reset,EGL_NV_stream_socket,EGL_NV_stream_socket_inet,EGL_NV_stream_socket_unix,EGL_NV_stream_sync,EGL_NV_sync,EGL_NV_system_time,EGL_TIZEN_image_native_buffer,EGL_TIZEN_image_native_surface"
    Online:
        Too many extensions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad_egl.h>

int gladLoadEGL(void) {
    return gladLoadEGLLoader((GLADloadproc)eglGetProcAddress);
}

PFNEGLSETBLOBCACHEFUNCSANDROIDPROC glad_eglSetBlobCacheFuncsANDROID;
PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC glad_eglCreateNativeClientBufferANDROID;
PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC glad_eglGetCompositorTimingSupportedANDROID;
PFNEGLGETCOMPOSITORTIMINGANDROIDPROC glad_eglGetCompositorTimingANDROID;
PFNEGLGETNEXTFRAMEIDANDROIDPROC glad_eglGetNextFrameIdANDROID;
PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC glad_eglGetFrameTimestampSupportedANDROID;
PFNEGLGETFRAMETIMESTAMPSANDROIDPROC glad_eglGetFrameTimestampsANDROID;
PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC glad_eglGetNativeClientBufferANDROID;
PFNEGLDUPNATIVEFENCEFDANDROIDPROC glad_eglDupNativeFenceFDANDROID;
PFNEGLPRESENTATIONTIMEANDROIDPROC glad_eglPresentationTimeANDROID;
PFNEGLQUERYSURFACEPOINTERANGLEPROC glad_eglQuerySurfacePointerANGLE;
PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC glad_eglCompositorSetContextListEXT;
PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC glad_eglCompositorSetContextAttributesEXT;
PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC glad_eglCompositorSetWindowListEXT;
PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC glad_eglCompositorSetWindowAttributesEXT;
PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC glad_eglCompositorBindTexWindowEXT;
PFNEGLCOMPOSITORSETSIZEEXTPROC glad_eglCompositorSetSizeEXT;
PFNEGLCOMPOSITORSWAPPOLICYEXTPROC glad_eglCompositorSwapPolicyEXT;
PFNEGLQUERYDEVICEATTRIBEXTPROC glad_eglQueryDeviceAttribEXT;
PFNEGLQUERYDEVICESTRINGEXTPROC glad_eglQueryDeviceStringEXT;
PFNEGLQUERYDEVICESEXTPROC glad_eglQueryDevicesEXT;
PFNEGLQUERYDISPLAYATTRIBEXTPROC glad_eglQueryDisplayAttribEXT;
PFNEGLQUERYDMABUFFORMATSEXTPROC glad_eglQueryDmaBufFormatsEXT;
PFNEGLQUERYDMABUFMODIFIERSEXTPROC glad_eglQueryDmaBufModifiersEXT;
PFNEGLGETOUTPUTLAYERSEXTPROC glad_eglGetOutputLayersEXT;
PFNEGLGETOUTPUTPORTSEXTPROC glad_eglGetOutputPortsEXT;
PFNEGLOUTPUTLAYERATTRIBEXTPROC glad_eglOutputLayerAttribEXT;
PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC glad_eglQueryOutputLayerAttribEXT;
PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC glad_eglQueryOutputLayerStringEXT;
PFNEGLOUTPUTPORTATTRIBEXTPROC glad_eglOutputPortAttribEXT;
PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC glad_eglQueryOutputPortAttribEXT;
PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC glad_eglQueryOutputPortStringEXT;
PFNEGLGETPLATFORMDISPLAYEXTPROC glad_eglGetPlatformDisplayEXT;
PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC glad_eglCreatePlatformWindowSurfaceEXT;
PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC glad_eglCreatePlatformPixmapSurfaceEXT;
PFNEGLSTREAMCONSUMEROUTPUTEXTPROC glad_eglStreamConsumerOutputEXT;
PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC glad_eglSwapBuffersWithDamageEXT;
PFNEGLCREATEPIXMAPSURFACEHIPROC glad_eglCreatePixmapSurfaceHI;
PFNEGLCREATESYNC64KHRPROC glad_eglCreateSync64KHR;
PFNEGLDEBUGMESSAGECONTROLKHRPROC glad_eglDebugMessageControlKHR;
PFNEGLQUERYDEBUGKHRPROC glad_eglQueryDebugKHR;
PFNEGLLABELOBJECTKHRPROC glad_eglLabelObjectKHR;
PFNEGLQUERYDISPLAYATTRIBKHRPROC glad_eglQueryDisplayAttribKHR;
PFNEGLCREATESYNCKHRPROC glad_eglCreateSyncKHR;
PFNEGLDESTROYSYNCKHRPROC glad_eglDestroySyncKHR;
PFNEGLCLIENTWAITSYNCKHRPROC glad_eglClientWaitSyncKHR;
PFNEGLGETSYNCATTRIBKHRPROC glad_eglGetSyncAttribKHR;
PFNEGLCREATEIMAGEKHRPROC glad_eglCreateImageKHR;
PFNEGLDESTROYIMAGEKHRPROC glad_eglDestroyImageKHR;
PFNEGLLOCKSURFACEKHRPROC glad_eglLockSurfaceKHR;
PFNEGLUNLOCKSURFACEKHRPROC glad_eglUnlockSurfaceKHR;
PFNEGLQUERYSURFACE64KHRPROC glad_eglQuerySurface64KHR;
PFNEGLSETDAMAGEREGIONKHRPROC glad_eglSetDamageRegionKHR;
PFNEGLSIGNALSYNCKHRPROC glad_eglSignalSyncKHR;
PFNEGLCREATESTREAMKHRPROC glad_eglCreateStreamKHR;
PFNEGLDESTROYSTREAMKHRPROC glad_eglDestroyStreamKHR;
PFNEGLSTREAMATTRIBKHRPROC glad_eglStreamAttribKHR;
PFNEGLQUERYSTREAMKHRPROC glad_eglQueryStreamKHR;
PFNEGLQUERYSTREAMU64KHRPROC glad_eglQueryStreamu64KHR;
PFNEGLCREATESTREAMATTRIBKHRPROC glad_eglCreateStreamAttribKHR;
PFNEGLSETSTREAMATTRIBKHRPROC glad_eglSetStreamAttribKHR;
PFNEGLQUERYSTREAMATTRIBKHRPROC glad_eglQueryStreamAttribKHR;
PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC glad_eglStreamConsumerAcquireAttribKHR;
PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC glad_eglStreamConsumerReleaseAttribKHR;
PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC glad_eglStreamConsumerGLTextureExternalKHR;
PFNEGLSTREAMCONSUMERACQUIREKHRPROC glad_eglStreamConsumerAcquireKHR;
PFNEGLSTREAMCONSUMERRELEASEKHRPROC glad_eglStreamConsumerReleaseKHR;
PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC glad_eglGetStreamFileDescriptorKHR;
PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC glad_eglCreateStreamFromFileDescriptorKHR;
PFNEGLQUERYSTREAMTIMEKHRPROC glad_eglQueryStreamTimeKHR;
PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC glad_eglCreateStreamProducerSurfaceKHR;
PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC glad_eglSwapBuffersWithDamageKHR;
PFNEGLWAITSYNCKHRPROC glad_eglWaitSyncKHR;
PFNEGLCREATEDRMIMAGEMESAPROC glad_eglCreateDRMImageMESA;
PFNEGLEXPORTDRMIMAGEMESAPROC glad_eglExportDRMImageMESA;
PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC glad_eglExportDMABUFImageQueryMESA;
PFNEGLEXPORTDMABUFIMAGEMESAPROC glad_eglExportDMABUFImageMESA;
PFNEGLSWAPBUFFERSREGIONNOKPROC glad_eglSwapBuffersRegionNOK;
PFNEGLSWAPBUFFERSREGION2NOKPROC glad_eglSwapBuffersRegion2NOK;
PFNEGLQUERYNATIVEDISPLAYNVPROC glad_eglQueryNativeDisplayNV;
PFNEGLQUERYNATIVEWINDOWNVPROC glad_eglQueryNativeWindowNV;
PFNEGLQUERYNATIVEPIXMAPNVPROC glad_eglQueryNativePixmapNV;
PFNEGLPOSTSUBBUFFERNVPROC glad_eglPostSubBufferNV;
PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC glad_eglStreamConsumerGLTextureExternalAttribsNV;
PFNEGLQUERYDISPLAYATTRIBNVPROC glad_eglQueryDisplayAttribNV;
PFNEGLSETSTREAMMETADATANVPROC glad_eglSetStreamMetadataNV;
PFNEGLQUERYSTREAMMETADATANVPROC glad_eglQueryStreamMetadataNV;
PFNEGLRESETSTREAMNVPROC glad_eglResetStreamNV;
PFNEGLCREATESTREAMSYNCNVPROC glad_eglCreateStreamSyncNV;
PFNEGLCREATEFENCESYNCNVPROC glad_eglCreateFenceSyncNV;
PFNEGLDESTROYSYNCNVPROC glad_eglDestroySyncNV;
PFNEGLFENCENVPROC glad_eglFenceNV;
PFNEGLCLIENTWAITSYNCNVPROC glad_eglClientWaitSyncNV;
PFNEGLSIGNALSYNCNVPROC glad_eglSignalSyncNV;
PFNEGLGETSYNCATTRIBNVPROC glad_eglGetSyncAttribNV;
PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC glad_eglGetSystemTimeFrequencyNV;
PFNEGLGETSYSTEMTIMENVPROC glad_eglGetSystemTimeNV;
static void load_EGL_ANDROID_blob_cache(GLADloadproc load) {
	glad_eglSetBlobCacheFuncsANDROID = (PFNEGLSETBLOBCACHEFUNCSANDROIDPROC)load("eglSetBlobCacheFuncsANDROID");
}
static void load_EGL_ANDROID_create_native_client_buffer(GLADloadproc load) {
	glad_eglCreateNativeClientBufferANDROID = (PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC)load("eglCreateNativeClientBufferANDROID");
}
static void load_EGL_ANDROID_get_frame_timestamps(GLADloadproc load) {
	glad_eglGetCompositorTimingSupportedANDROID = (PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC)load("eglGetCompositorTimingSupportedANDROID");
	glad_eglGetCompositorTimingANDROID = (PFNEGLGETCOMPOSITORTIMINGANDROIDPROC)load("eglGetCompositorTimingANDROID");
	glad_eglGetNextFrameIdANDROID = (PFNEGLGETNEXTFRAMEIDANDROIDPROC)load("eglGetNextFrameIdANDROID");
	glad_eglGetFrameTimestampSupportedANDROID = (PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC)load("eglGetFrameTimestampSupportedANDROID");
	glad_eglGetFrameTimestampsANDROID = (PFNEGLGETFRAMETIMESTAMPSANDROIDPROC)load("eglGetFrameTimestampsANDROID");
}
static void load_EGL_ANDROID_get_native_client_buffer(GLADloadproc load) {
	glad_eglGetNativeClientBufferANDROID = (PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC)load("eglGetNativeClientBufferANDROID");
}
static void load_EGL_ANDROID_native_fence_sync(GLADloadproc load) {
	glad_eglDupNativeFenceFDANDROID = (PFNEGLDUPNATIVEFENCEFDANDROIDPROC)load("eglDupNativeFenceFDANDROID");
}
static void load_EGL_ANDROID_presentation_time(GLADloadproc load) {
	glad_eglPresentationTimeANDROID = (PFNEGLPRESENTATIONTIMEANDROIDPROC)load("eglPresentationTimeANDROID");
}
static void load_EGL_ANGLE_query_surface_pointer(GLADloadproc load) {
	glad_eglQuerySurfacePointerANGLE = (PFNEGLQUERYSURFACEPOINTERANGLEPROC)load("eglQuerySurfacePointerANGLE");
}
static void load_EGL_EXT_compositor(GLADloadproc load) {
	glad_eglCompositorSetContextListEXT = (PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC)load("eglCompositorSetContextListEXT");
	glad_eglCompositorSetContextAttributesEXT = (PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC)load("eglCompositorSetContextAttributesEXT");
	glad_eglCompositorSetWindowListEXT = (PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC)load("eglCompositorSetWindowListEXT");
	glad_eglCompositorSetWindowAttributesEXT = (PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC)load("eglCompositorSetWindowAttributesEXT");
	glad_eglCompositorBindTexWindowEXT = (PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC)load("eglCompositorBindTexWindowEXT");
	glad_eglCompositorSetSizeEXT = (PFNEGLCOMPOSITORSETSIZEEXTPROC)load("eglCompositorSetSizeEXT");
	glad_eglCompositorSwapPolicyEXT = (PFNEGLCOMPOSITORSWAPPOLICYEXTPROC)load("eglCompositorSwapPolicyEXT");
}
static void load_EGL_EXT_device_base(GLADloadproc load) {
	glad_eglQueryDeviceAttribEXT = (PFNEGLQUERYDEVICEATTRIBEXTPROC)load("eglQueryDeviceAttribEXT");
	glad_eglQueryDeviceStringEXT = (PFNEGLQUERYDEVICESTRINGEXTPROC)load("eglQueryDeviceStringEXT");
	glad_eglQueryDevicesEXT = (PFNEGLQUERYDEVICESEXTPROC)load("eglQueryDevicesEXT");
	glad_eglQueryDisplayAttribEXT = (PFNEGLQUERYDISPLAYATTRIBEXTPROC)load("eglQueryDisplayAttribEXT");
}
static void load_EGL_EXT_device_enumeration(GLADloadproc load) {
	glad_eglQueryDevicesEXT = (PFNEGLQUERYDEVICESEXTPROC)load("eglQueryDevicesEXT");
}
static void load_EGL_EXT_device_query(GLADloadproc load) {
	glad_eglQueryDeviceAttribEXT = (PFNEGLQUERYDEVICEATTRIBEXTPROC)load("eglQueryDeviceAttribEXT");
	glad_eglQueryDeviceStringEXT = (PFNEGLQUERYDEVICESTRINGEXTPROC)load("eglQueryDeviceStringEXT");
	glad_eglQueryDisplayAttribEXT = (PFNEGLQUERYDISPLAYATTRIBEXTPROC)load("eglQueryDisplayAttribEXT");
}
static void load_EGL_EXT_image_dma_buf_import_modifiers(GLADloadproc load) {
	glad_eglQueryDmaBufFormatsEXT = (PFNEGLQUERYDMABUFFORMATSEXTPROC)load("eglQueryDmaBufFormatsEXT");
	glad_eglQueryDmaBufModifiersEXT = (PFNEGLQUERYDMABUFMODIFIERSEXTPROC)load("eglQueryDmaBufModifiersEXT");
}
static void load_EGL_EXT_output_base(GLADloadproc load) {
	glad_eglGetOutputLayersEXT = (PFNEGLGETOUTPUTLAYERSEXTPROC)load("eglGetOutputLayersEXT");
	glad_eglGetOutputPortsEXT = (PFNEGLGETOUTPUTPORTSEXTPROC)load("eglGetOutputPortsEXT");
	glad_eglOutputLayerAttribEXT = (PFNEGLOUTPUTLAYERATTRIBEXTPROC)load("eglOutputLayerAttribEXT");
	glad_eglQueryOutputLayerAttribEXT = (PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC)load("eglQueryOutputLayerAttribEXT");
	glad_eglQueryOutputLayerStringEXT = (PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC)load("eglQueryOutputLayerStringEXT");
	glad_eglOutputPortAttribEXT = (PFNEGLOUTPUTPORTATTRIBEXTPROC)load("eglOutputPortAttribEXT");
	glad_eglQueryOutputPortAttribEXT = (PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC)load("eglQueryOutputPortAttribEXT");
	glad_eglQueryOutputPortStringEXT = (PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC)load("eglQueryOutputPortStringEXT");
}
static void load_EGL_EXT_platform_base(GLADloadproc load) {
	glad_eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)load("eglGetPlatformDisplayEXT");
	glad_eglCreatePlatformWindowSurfaceEXT = (PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC)load("eglCreatePlatformWindowSurfaceEXT");
	glad_eglCreatePlatformPixmapSurfaceEXT = (PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC)load("eglCreatePlatformPixmapSurfaceEXT");
}
static void load_EGL_EXT_stream_consumer_egloutput(GLADloadproc load) {
	glad_eglStreamConsumerOutputEXT = (PFNEGLSTREAMCONSUMEROUTPUTEXTPROC)load("eglStreamConsumerOutputEXT");
}
static void load_EGL_EXT_swap_buffers_with_damage(GLADloadproc load) {
	glad_eglSwapBuffersWithDamageEXT = (PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)load("eglSwapBuffersWithDamageEXT");
}
static void load_EGL_HI_clientpixmap(GLADloadproc load) {
	glad_eglCreatePixmapSurfaceHI = (PFNEGLCREATEPIXMAPSURFACEHIPROC)load("eglCreatePixmapSurfaceHI");
}
static void load_EGL_KHR_cl_event2(GLADloadproc load) {
	glad_eglCreateSync64KHR = (PFNEGLCREATESYNC64KHRPROC)load("eglCreateSync64KHR");
}
static void load_EGL_KHR_debug(GLADloadproc load) {
	glad_eglDebugMessageControlKHR = (PFNEGLDEBUGMESSAGECONTROLKHRPROC)load("eglDebugMessageControlKHR");
	glad_eglQueryDebugKHR = (PFNEGLQUERYDEBUGKHRPROC)load("eglQueryDebugKHR");
	glad_eglLabelObjectKHR = (PFNEGLLABELOBJECTKHRPROC)load("eglLabelObjectKHR");
}
static void load_EGL_KHR_display_reference(GLADloadproc load) {
	glad_eglQueryDisplayAttribKHR = (PFNEGLQUERYDISPLAYATTRIBKHRPROC)load("eglQueryDisplayAttribKHR");
}
static void load_EGL_KHR_fence_sync(GLADloadproc load) {
	glad_eglCreateSyncKHR = (PFNEGLCREATESYNCKHRPROC)load("eglCreateSyncKHR");
	glad_eglDestroySyncKHR = (PFNEGLDESTROYSYNCKHRPROC)load("eglDestroySyncKHR");
	glad_eglClientWaitSyncKHR = (PFNEGLCLIENTWAITSYNCKHRPROC)load("eglClientWaitSyncKHR");
	glad_eglGetSyncAttribKHR = (PFNEGLGETSYNCATTRIBKHRPROC)load("eglGetSyncAttribKHR");
}
static void load_EGL_KHR_image(GLADloadproc load) {
	glad_eglCreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC)load("eglCreateImageKHR");
	glad_eglDestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC)load("eglDestroyImageKHR");
}
static void load_EGL_KHR_image_base(GLADloadproc load) {
	glad_eglCreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC)load("eglCreateImageKHR");
	glad_eglDestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC)load("eglDestroyImageKHR");
}
static void load_EGL_KHR_lock_surface(GLADloadproc load) {
	glad_eglLockSurfaceKHR = (PFNEGLLOCKSURFACEKHRPROC)load("eglLockSurfaceKHR");
	glad_eglUnlockSurfaceKHR = (PFNEGLUNLOCKSURFACEKHRPROC)load("eglUnlockSurfaceKHR");
}
static void load_EGL_KHR_lock_surface3(GLADloadproc load) {
	glad_eglLockSurfaceKHR = (PFNEGLLOCKSURFACEKHRPROC)load("eglLockSurfaceKHR");
	glad_eglUnlockSurfaceKHR = (PFNEGLUNLOCKSURFACEKHRPROC)load("eglUnlockSurfaceKHR");
	glad_eglQuerySurface64KHR = (PFNEGLQUERYSURFACE64KHRPROC)load("eglQuerySurface64KHR");
}
static void load_EGL_KHR_partial_update(GLADloadproc load) {
	glad_eglSetDamageRegionKHR = (PFNEGLSETDAMAGEREGIONKHRPROC)load("eglSetDamageRegionKHR");
}
static void load_EGL_KHR_reusable_sync(GLADloadproc load) {
	glad_eglCreateSyncKHR = (PFNEGLCREATESYNCKHRPROC)load("eglCreateSyncKHR");
	glad_eglDestroySyncKHR = (PFNEGLDESTROYSYNCKHRPROC)load("eglDestroySyncKHR");
	glad_eglClientWaitSyncKHR = (PFNEGLCLIENTWAITSYNCKHRPROC)load("eglClientWaitSyncKHR");
	glad_eglSignalSyncKHR = (PFNEGLSIGNALSYNCKHRPROC)load("eglSignalSyncKHR");
	glad_eglGetSyncAttribKHR = (PFNEGLGETSYNCATTRIBKHRPROC)load("eglGetSyncAttribKHR");
}
static void load_EGL_KHR_stream(GLADloadproc load) {
	glad_eglCreateStreamKHR = (PFNEGLCREATESTREAMKHRPROC)load("eglCreateStreamKHR");
	glad_eglDestroyStreamKHR = (PFNEGLDESTROYSTREAMKHRPROC)load("eglDestroyStreamKHR");
	glad_eglStreamAttribKHR = (PFNEGLSTREAMATTRIBKHRPROC)load("eglStreamAttribKHR");
	glad_eglQueryStreamKHR = (PFNEGLQUERYSTREAMKHRPROC)load("eglQueryStreamKHR");
	glad_eglQueryStreamu64KHR = (PFNEGLQUERYSTREAMU64KHRPROC)load("eglQueryStreamu64KHR");
}
static void load_EGL_KHR_stream_attrib(GLADloadproc load) {
	glad_eglCreateStreamAttribKHR = (PFNEGLCREATESTREAMATTRIBKHRPROC)load("eglCreateStreamAttribKHR");
	glad_eglSetStreamAttribKHR = (PFNEGLSETSTREAMATTRIBKHRPROC)load("eglSetStreamAttribKHR");
	glad_eglQueryStreamAttribKHR = (PFNEGLQUERYSTREAMATTRIBKHRPROC)load("eglQueryStreamAttribKHR");
	glad_eglStreamConsumerAcquireAttribKHR = (PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC)load("eglStreamConsumerAcquireAttribKHR");
	glad_eglStreamConsumerReleaseAttribKHR = (PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC)load("eglStreamConsumerReleaseAttribKHR");
}
static void load_EGL_KHR_stream_consumer_gltexture(GLADloadproc load) {
	glad_eglStreamConsumerGLTextureExternalKHR = (PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC)load("eglStreamConsumerGLTextureExternalKHR");
	glad_eglStreamConsumerAcquireKHR = (PFNEGLSTREAMCONSUMERACQUIREKHRPROC)load("eglStreamConsumerAcquireKHR");
	glad_eglStreamConsumerReleaseKHR = (PFNEGLSTREAMCONSUMERRELEASEKHRPROC)load("eglStreamConsumerReleaseKHR");
}
static void load_EGL_KHR_stream_cross_process_fd(GLADloadproc load) {
	glad_eglGetStreamFileDescriptorKHR = (PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC)load("eglGetStreamFileDescriptorKHR");
	glad_eglCreateStreamFromFileDescriptorKHR = (PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC)load("eglCreateStreamFromFileDescriptorKHR");
}
static void load_EGL_KHR_stream_fifo(GLADloadproc load) {
	glad_eglQueryStreamTimeKHR = (PFNEGLQUERYSTREAMTIMEKHRPROC)load("eglQueryStreamTimeKHR");
}
static void load_EGL_KHR_stream_producer_eglsurface(GLADloadproc load) {
	glad_eglCreateStreamProducerSurfaceKHR = (PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC)load("eglCreateStreamProducerSurfaceKHR");
}
static void load_EGL_KHR_swap_buffers_with_damage(GLADloadproc load) {
	glad_eglSwapBuffersWithDamageKHR = (PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC)load("eglSwapBuffersWithDamageKHR");
}
static void load_EGL_KHR_wait_sync(GLADloadproc load) {
	glad_eglWaitSyncKHR = (PFNEGLWAITSYNCKHRPROC)load("eglWaitSyncKHR");
}
static void load_EGL_MESA_drm_image(GLADloadproc load) {
	glad_eglCreateDRMImageMESA = (PFNEGLCREATEDRMIMAGEMESAPROC)load("eglCreateDRMImageMESA");
	glad_eglExportDRMImageMESA = (PFNEGLEXPORTDRMIMAGEMESAPROC)load("eglExportDRMImageMESA");
}
static void load_EGL_MESA_image_dma_buf_export(GLADloadproc load) {
	glad_eglExportDMABUFImageQueryMESA = (PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC)load("eglExportDMABUFImageQueryMESA");
	glad_eglExportDMABUFImageMESA = (PFNEGLEXPORTDMABUFIMAGEMESAPROC)load("eglExportDMABUFImageMESA");
}
static void load_EGL_NOK_swap_region(GLADloadproc load) {
	glad_eglSwapBuffersRegionNOK = (PFNEGLSWAPBUFFERSREGIONNOKPROC)load("eglSwapBuffersRegionNOK");
}
static void load_EGL_NOK_swap_region2(GLADloadproc load) {
	glad_eglSwapBuffersRegion2NOK = (PFNEGLSWAPBUFFERSREGION2NOKPROC)load("eglSwapBuffersRegion2NOK");
}
static void load_EGL_NV_native_query(GLADloadproc load) {
	glad_eglQueryNativeDisplayNV = (PFNEGLQUERYNATIVEDISPLAYNVPROC)load("eglQueryNativeDisplayNV");
	glad_eglQueryNativeWindowNV = (PFNEGLQUERYNATIVEWINDOWNVPROC)load("eglQueryNativeWindowNV");
	glad_eglQueryNativePixmapNV = (PFNEGLQUERYNATIVEPIXMAPNVPROC)load("eglQueryNativePixmapNV");
}
static void load_EGL_NV_post_sub_buffer(GLADloadproc load) {
	glad_eglPostSubBufferNV = (PFNEGLPOSTSUBBUFFERNVPROC)load("eglPostSubBufferNV");
}
static void load_EGL_NV_stream_consumer_gltexture_yuv(GLADloadproc load) {
	glad_eglStreamConsumerGLTextureExternalAttribsNV = (PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC)load("eglStreamConsumerGLTextureExternalAttribsNV");
}
static void load_EGL_NV_stream_metadata(GLADloadproc load) {
	glad_eglQueryDisplayAttribNV = (PFNEGLQUERYDISPLAYATTRIBNVPROC)load("eglQueryDisplayAttribNV");
	glad_eglSetStreamMetadataNV = (PFNEGLSETSTREAMMETADATANVPROC)load("eglSetStreamMetadataNV");
	glad_eglQueryStreamMetadataNV = (PFNEGLQUERYSTREAMMETADATANVPROC)load("eglQueryStreamMetadataNV");
}
static void load_EGL_NV_stream_reset(GLADloadproc load) {
	glad_eglResetStreamNV = (PFNEGLRESETSTREAMNVPROC)load("eglResetStreamNV");
}
static void load_EGL_NV_stream_sync(GLADloadproc load) {
	glad_eglCreateStreamSyncNV = (PFNEGLCREATESTREAMSYNCNVPROC)load("eglCreateStreamSyncNV");
}
static void load_EGL_NV_sync(GLADloadproc load) {
	glad_eglCreateFenceSyncNV = (PFNEGLCREATEFENCESYNCNVPROC)load("eglCreateFenceSyncNV");
	glad_eglDestroySyncNV = (PFNEGLDESTROYSYNCNVPROC)load("eglDestroySyncNV");
	glad_eglFenceNV = (PFNEGLFENCENVPROC)load("eglFenceNV");
	glad_eglClientWaitSyncNV = (PFNEGLCLIENTWAITSYNCNVPROC)load("eglClientWaitSyncNV");
	glad_eglSignalSyncNV = (PFNEGLSIGNALSYNCNVPROC)load("eglSignalSyncNV");
	glad_eglGetSyncAttribNV = (PFNEGLGETSYNCATTRIBNVPROC)load("eglGetSyncAttribNV");
}
static void load_EGL_NV_system_time(GLADloadproc load) {
	glad_eglGetSystemTimeFrequencyNV = (PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC)load("eglGetSystemTimeFrequencyNV");
	glad_eglGetSystemTimeNV = (PFNEGLGETSYSTEMTIMENVPROC)load("eglGetSystemTimeNV");
}
static int find_extensionsEGL(void) {
	return 1;
}

static void find_coreEGL(void) {
}

int gladLoadEGLLoader(GLADloadproc load) {
	(void) load;
	find_coreEGL();

	if (!find_extensionsEGL()) return 0;
	load_EGL_ANDROID_blob_cache(load);
	load_EGL_ANDROID_create_native_client_buffer(load);
	load_EGL_ANDROID_get_frame_timestamps(load);
	load_EGL_ANDROID_get_native_client_buffer(load);
	load_EGL_ANDROID_native_fence_sync(load);
	load_EGL_ANDROID_presentation_time(load);
	load_EGL_ANGLE_query_surface_pointer(load);
	load_EGL_EXT_compositor(load);
	load_EGL_EXT_device_base(load);
	load_EGL_EXT_device_enumeration(load);
	load_EGL_EXT_device_query(load);
	load_EGL_EXT_image_dma_buf_import_modifiers(load);
	load_EGL_EXT_output_base(load);
	load_EGL_EXT_platform_base(load);
	load_EGL_EXT_stream_consumer_egloutput(load);
	load_EGL_EXT_swap_buffers_with_damage(load);
	load_EGL_HI_clientpixmap(load);
	load_EGL_KHR_cl_event2(load);
	load_EGL_KHR_debug(load);
	load_EGL_KHR_display_reference(load);
	load_EGL_KHR_fence_sync(load);
	load_EGL_KHR_image(load);
	load_EGL_KHR_image_base(load);
	load_EGL_KHR_lock_surface(load);
	load_EGL_KHR_lock_surface3(load);
	load_EGL_KHR_partial_update(load);
	load_EGL_KHR_reusable_sync(load);
	load_EGL_KHR_stream(load);
	load_EGL_KHR_stream_attrib(load);
	load_EGL_KHR_stream_consumer_gltexture(load);
	load_EGL_KHR_stream_cross_process_fd(load);
	load_EGL_KHR_stream_fifo(load);
	load_EGL_KHR_stream_producer_eglsurface(load);
	load_EGL_KHR_swap_buffers_with_damage(load);
	load_EGL_KHR_wait_sync(load);
	load_EGL_MESA_drm_image(load);
	load_EGL_MESA_image_dma_buf_export(load);
	load_EGL_NOK_swap_region(load);
	load_EGL_NOK_swap_region2(load);
	load_EGL_NV_native_query(load);
	load_EGL_NV_post_sub_buffer(load);
	load_EGL_NV_stream_consumer_gltexture_yuv(load);
	load_EGL_NV_stream_metadata(load);
	load_EGL_NV_stream_reset(load);
	load_EGL_NV_stream_sync(load);
	load_EGL_NV_sync(load);
	load_EGL_NV_system_time(load);
	return 1;
}

