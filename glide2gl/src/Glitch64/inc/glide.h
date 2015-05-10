#ifndef __GLIDE_H__
#define __GLIDE_H__

#include <3dfx.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL_opengles2.h>
#include "boolean.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
** -----------------------------------------------------------------------
** TYPE DEFINITIONS
** -----------------------------------------------------------------------
*/
typedef int (*GrProc)();

/*
** -----------------------------------------------------------------------
** CONSTANTS AND TYPES
** -----------------------------------------------------------------------
*/
#define GR_NULL_MIPMAP_HANDLE  ((GrMipMapId_t) -1)

#define GR_MIPMAPLEVELMASK_EVEN  FXBIT(0)
#define GR_MIPMAPLEVELMASK_ODD  FXBIT(1)
#define GR_MIPMAPLEVELMASK_BOTH (GR_MIPMAPLEVELMASK_EVEN | GR_MIPMAPLEVELMASK_ODD )

#define GR_LODBIAS_BILINEAR     0.5
#define GR_LODBIAS_TRILINEAR    0.0

#define GR_TMU0         0x0
#define GR_TMU1         0x1
#define GR_TMU2         0x2

#define GR_FBI          0x0

#define GR_COMBINE_FUNCTION_ZERO        0x0
#define GR_COMBINE_FUNCTION_NONE        GR_COMBINE_FUNCTION_ZERO
#define GR_COMBINE_FUNCTION_LOCAL       0x1
#define GR_COMBINE_FUNCTION_LOCAL_ALPHA 0x2
#define GR_COMBINE_FUNCTION_SCALE_OTHER 0x3
#define GR_COMBINE_FUNCTION_BLEND_OTHER GR_COMBINE_FUNCTION_SCALE_OTHER
#define GR_COMBINE_FUNCTION_SCALE_OTHER_ADD_LOCAL 0x4
#define GR_COMBINE_FUNCTION_SCALE_OTHER_ADD_LOCAL_ALPHA 0x5 
#define GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL 0x6
#define GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL_ADD_LOCAL 0x7
#define GR_COMBINE_FUNCTION_BLEND GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL_ADD_LOCAL
#define GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL_ADD_LOCAL_ALPHA 0x8
#define GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL 0x9
#define GR_COMBINE_FUNCTION_BLEND_LOCAL GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL
#define GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL_ALPHA 0x10

#define GR_COMBINE_FACTOR_ZERO          0x0
#define GR_COMBINE_FACTOR_NONE          GR_COMBINE_FACTOR_ZERO
#define GR_COMBINE_FACTOR_LOCAL         0x1
#define GR_COMBINE_FACTOR_OTHER_ALPHA   0x2
#define GR_COMBINE_FACTOR_LOCAL_ALPHA   0x3
#define GR_COMBINE_FACTOR_TEXTURE_ALPHA 0x4
#define GR_COMBINE_FACTOR_TEXTURE_RGB   0x5
#define GR_COMBINE_FACTOR_DETAIL_FACTOR GR_COMBINE_FACTOR_TEXTURE_ALPHA
#define GR_COMBINE_FACTOR_LOD_FRACTION  0x5
#define GR_COMBINE_FACTOR_ONE           0x8
#define GR_COMBINE_FACTOR_ONE_MINUS_LOCAL 0x9
#define GR_COMBINE_FACTOR_ONE_MINUS_OTHER_ALPHA 0xa
#define GR_COMBINE_FACTOR_ONE_MINUS_LOCAL_ALPHA 0xb
#define GR_COMBINE_FACTOR_ONE_MINUS_TEXTURE_ALPHA 0xc
#define GR_COMBINE_FACTOR_ONE_MINUS_DETAIL_FACTOR GR_COMBINE_FACTOR_ONE_MINUS_TEXTURE_ALPHA
#define GR_COMBINE_FACTOR_ONE_MINUS_LOD_FRACTION 0xd


#define GR_COMBINE_LOCAL_ITERATED 0x0
#define GR_COMBINE_LOCAL_CONSTANT 0x1
#define GR_COMBINE_LOCAL_NONE GR_COMBINE_LOCAL_CONSTANT
#define GR_COMBINE_LOCAL_DEPTH  0x2

#define GR_COMBINE_OTHER_ITERATED 0x0
#define GR_COMBINE_OTHER_TEXTURE 0x1
#define GR_COMBINE_OTHER_CONSTANT 0x2
#define GR_COMBINE_OTHER_NONE GR_COMBINE_OTHER_CONSTANT

#define GR_ALPHASOURCE_CC_ALPHA 0x0
#define GR_ALPHASOURCE_ITERATED_ALPHA 0x1
#define GR_ALPHASOURCE_TEXTURE_ALPHA 0x2
#define GR_ALPHASOURCE_TEXTURE_ALPHA_TIMES_ITERATED_ALPHA 0x3

#define GR_COLORCOMBINE_ZERO 0x0
#define GR_COLORCOMBINE_CCRGB 0x1
#define GR_COLORCOMBINE_ITRGB 0x2
#define GR_COLORCOMBINE_ITRGB_DELTA0 0x3
#define GR_COLORCOMBINE_DECAL_TEXTURE 0x4
#define GR_COLORCOMBINE_TEXTURE_TIMES_CCRGB 0x5
#define GR_COLORCOMBINE_TEXTURE_TIMES_ITRGB 0x6
#define GR_COLORCOMBINE_TEXTURE_TIMES_ITRGB_DELTA0 0x7
#define GR_COLORCOMBINE_TEXTURE_TIMES_ITRGB_ADD_ALPHA 0x8
#define GR_COLORCOMBINE_TEXTURE_TIMES_ALPHA 0x9
#define GR_COLORCOMBINE_TEXTURE_TIMES_ALPHA_ADD_ITRGB 0xa
#define GR_COLORCOMBINE_TEXTURE_ADD_ITRGB 0xb
#define GR_COLORCOMBINE_TEXTURE_SUB_ITRGB 0xc
#define GR_COLORCOMBINE_CCRGB_BLEND_ITRGB_ON_TEXALPHA 0xd
#define GR_COLORCOMBINE_DIFF_SPEC_A 0xe
#define GR_COLORCOMBINE_DIFF_SPEC_B 0xf
#define GR_COLORCOMBINE_ONE 0x10

#define GR_BLEND_ZERO GL_ZERO
#define GR_BLEND_SRC_ALPHA GL_SRC_ALPHA
#define GR_BLEND_SRC_COLOR 0x2
#define GR_BLEND_DST_COLOR GR_BLEND_SRC_COLOR
#define GR_BLEND_DST_ALPHA 0x3 
#define GR_BLEND_ONE GL_ONE
#define GR_BLEND_ONE_MINUS_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
#define GR_BLEND_ONE_MINUS_SRC_COLOR 0x6
#define GR_BLEND_ONE_MINUS_DST_COLOR GR_BLEND_ONE_MINUS_SRC_COLOR 
#define GR_BLEND_ONE_MINUS_DST_ALPHA 0x7
#define GR_BLEND_RESERVED_8 0x8
#define GR_BLEND_RESERVED_9 0x9
#define GR_BLEND_RESERVED_A 0xa
#define GR_BLEND_RESERVED_B 0xb
#define GR_BLEND_RESERVED_C 0xc
#define GR_BLEND_RESERVED_D 0xd
#define GR_BLEND_RESERVED_E 0xe
#define GR_BLEND_ALPHA_SATURATE 0xf
#define GR_BLEND_PREFOG_COLOR GR_BLEND_ALPHA_SATURATE

#define GR_ASPECT_LOG2_8x1        3       /* 8W x 1H */
#define GR_ASPECT_LOG2_4x1        2       /* 4W x 1H */
#define GR_ASPECT_LOG2_2x1        1       /* 2W x 1H */
#define GR_ASPECT_LOG2_1x1        0       /* 1W x 1H */
#define GR_ASPECT_LOG2_1x2       -1       /* 1W x 2H */
#define GR_ASPECT_LOG2_1x4       -2       /* 1W x 4H */
#define GR_ASPECT_LOG2_1x8       -3       /* 1W x 8H */

#define GR_BUFFER_FRONTBUFFER   0x0
#define GR_BUFFER_BACKBUFFER    0x1
#define GR_BUFFER_AUXBUFFER     0x2
#define GR_BUFFER_DEPTHBUFFER   0x3
#define GR_BUFFER_ALPHABUFFER   0x4
#define GR_BUFFER_TRIPLEBUFFER  0x5

#define GR_CHROMAKEY_DISABLE    0x0
#define GR_CHROMAKEY_ENABLE     0x1

#define GR_CHROMARANGE_RGB_ALL_EXT  0x0

#define GR_CHROMARANGE_DISABLE_EXT  0x00
#define GR_CHROMARANGE_ENABLE_EXT   0x01

#define GR_TEXCHROMA_DISABLE_EXT               0x0
#define GR_TEXCHROMA_ENABLE_EXT                0x1

#define GR_TEXCHROMARANGE_RGB_ALL_EXT  0x0

#define GR_CMP_NEVER    GL_NEVER
#define GR_CMP_LESS     GL_LESS
#define GR_CMP_EQUAL    GL_EQUAL
#define GR_CMP_LEQUAL   GL_LEQUAL
#define GR_CMP_GREATER  GL_GREATER
#define GR_CMP_NOTEQUAL GL_NOTEQUAL
#define GR_CMP_GEQUAL   GL_EQUAL
#define GR_CMP_ALWAYS   GL_ALWAYS

#define GR_COLORFORMAT_ARGB     0x0
#define GR_COLORFORMAT_ABGR     0x1

#define GR_COLORFORMAT_RGBA     0x2
#define GR_COLORFORMAT_BGRA     0x3

#define GR_CULL_DISABLE         0x0
#define GR_CULL_NEGATIVE        0x1
#define GR_CULL_POSITIVE        0x2

#define GR_DEPTHBUFFER_DISABLE                  0x0
#define GR_DEPTHBUFFER_ZBUFFER                  0x1
#define GR_DEPTHBUFFER_WBUFFER                  0x2
#define GR_DEPTHBUFFER_ZBUFFER_COMPARE_TO_BIAS  0x3
#define GR_DEPTHBUFFER_WBUFFER_COMPARE_TO_BIAS  0x4

#define GR_DITHER_DISABLE       0x0
#define GR_DITHER_2x2           0x1
#define GR_DITHER_4x4           0x2

#define GR_STIPPLE_DISABLE	0x0
#define GR_STIPPLE_PATTERN	0x1
#define GR_STIPPLE_ROTATE	0x2

#define GR_FOG_DISABLE                     0x0
#define GR_FOG_WITH_TABLE_ON_Q             0x1
#define GR_FOG_WITH_TABLE_ON_FOGCOORD_EXT  0x2

#define GR_LFB_READ_ONLY  0x00
#define GR_LFB_WRITE_ONLY 0x01
#define GR_LFB_IDLE       0x00
#define GR_LFB_NOIDLE     0x10

#define GR_LFB_WRITE_ONLY_EXPLICIT_EXT	0x02 /* explicitly not allow reading from the lfb pointer */

#define GR_LFBBYPASS_DISABLE    0x0
#define GR_LFBBYPASS_ENABLE     0x1

#define GR_LFBWRITEMODE_565        0x0 /* RGB:RGB */
#define GR_LFBWRITEMODE_555        0x1 /* RGB:RGB */
#define GR_LFBWRITEMODE_1555       0x2 /* ARGB:ARGB */
#define GR_LFBWRITEMODE_RESERVED1  0x3
#define GR_LFBWRITEMODE_888        0x4 /* RGB */
#define GR_LFBWRITEMODE_8888       0x5 /* ARGB */
#define GR_LFBWRITEMODE_RESERVED2  0x6
#define GR_LFBWRITEMODE_RESERVED3  0x7
#define GR_LFBWRITEMODE_RESERVED4  0x8
#define GR_LFBWRITEMODE_RESERVED5  0x9
#define GR_LFBWRITEMODE_RESERVED6  0xa
#define GR_LFBWRITEMODE_RESERVED7  0xb
#define GR_LFBWRITEMODE_565_DEPTH  0xc /* RGB:DEPTH */
#define GR_LFBWRITEMODE_555_DEPTH  0xd /* RGB:DEPTH */
#define GR_LFBWRITEMODE_1555_DEPTH 0xe /* ARGB:DEPTH */
#define GR_LFBWRITEMODE_ZA16       0xf /* DEPTH:DEPTH */
#define GR_LFBWRITEMODE_ANY        0xFF


#define GR_ORIGIN_UPPER_LEFT    0x0
#define GR_ORIGIN_LOWER_LEFT    0x1
#define GR_ORIGIN_ANY           0xFF

typedef struct {
    int                size;
    void               *lfbPtr;
    uint32_t              strideInBytes;        
    int32_t   writeMode;
    int32_t origin;
} GrLfbInfo_t;

#define GR_LOD_LOG2_256         0x8
#define GR_LOD_LOG2_128         0x7
#define GR_LOD_LOG2_64          0x6
#define GR_LOD_LOG2_32          0x5
#define GR_LOD_LOG2_16          0x4
#define GR_LOD_LOG2_8           0x3
#define GR_LOD_LOG2_4           0x2
#define GR_LOD_LOG2_2           0x1
#define GR_LOD_LOG2_1           0x0

#define GR_MIPMAP_DISABLE               0x0 /* no mip mapping  */
#define GR_MIPMAP_NEAREST               0x1 /* use nearest mipmap */
#define GR_MIPMAP_NEAREST_DITHER        0x2 /* GR_MIPMAP_NEAREST + LOD dith */

#define GR_SMOOTHING_DISABLE    0x0
#define GR_SMOOTHING_ENABLE     0x1

#define GR_TEXTURECLAMP_WRAP        GL_REPEAT
#define GR_TEXTURECLAMP_CLAMP       GL_CLAMP_TO_EDGE
#define GR_TEXTURECLAMP_MIRROR_EXT  GL_MIRRORED_REPEAT

#define GR_TEXTURECOMBINE_ZERO          0x0 /* texout = 0 */
#define GR_TEXTURECOMBINE_DECAL         0x1 /* texout = texthis */
#define GR_TEXTURECOMBINE_OTHER         0x2 /* this TMU in passthru mode */
#define GR_TEXTURECOMBINE_ADD           0x3 /* tout = tthis + t(this+1) */
#define GR_TEXTURECOMBINE_MULTIPLY      0x4 /* texout = tthis * t(this+1) */
#define GR_TEXTURECOMBINE_SUBTRACT      0x5 /* Sutract from upstream TMU */
#define GR_TEXTURECOMBINE_DETAIL        0x6 /* detail--detail on tthis */
#define GR_TEXTURECOMBINE_DETAIL_OTHER  0x7 /* detail--detail on tthis+1 */
#define GR_TEXTURECOMBINE_TRILINEAR_ODD 0x8 /* trilinear--odd levels tthis*/
#define GR_TEXTURECOMBINE_TRILINEAR_EVEN 0x9 /*trilinear--even levels tthis*/
#define GR_TEXTURECOMBINE_ONE           0xa /* texout = 0xFFFFFFFF */

#define GR_TEXTUREFILTER_POINT_SAMPLED  0x0
#define GR_TEXTUREFILTER_3POINT_LINEAR  0x1
#define GR_TEXTUREFILTER_BILINEAR       0x2

/* KoolSmoky - */
#define GR_TEXFMT_8BIT                  0x0
#define GR_TEXFMT_RGB_332               GR_TEXFMT_8BIT
#define GR_TEXFMT_YIQ_422               0x1
#define GR_TEXFMT_ALPHA_8               0x2 /* (0..0xFF) alpha     */
#define GR_TEXFMT_INTENSITY_8           0x3 /* (0..0xFF) intensity */
#define GR_TEXFMT_ALPHA_INTENSITY_44    0x4
#define GR_TEXFMT_P_8                   0x5 /* 8-bit palette */
#define GR_TEXFMT_RSVD0                 0x6 /* GR_TEXFMT_P_8_RGBA */
#define GR_TEXFMT_P_8_6666              GR_TEXFMT_RSVD0
#define GR_TEXFMT_P_8_6666_EXT          GR_TEXFMT_RSVD0
#define GR_TEXFMT_RSVD1                 0x7
#define GR_TEXFMT_16BIT                 0x8
#define GR_TEXFMT_ARGB_8332             GR_TEXFMT_16BIT
#define GR_TEXFMT_AYIQ_8422             0x9
#define GR_TEXFMT_RGB_565               0xa
#define GR_TEXFMT_ARGB_1555             0xb
#define GR_TEXFMT_ARGB_4444             0xc
#define GR_TEXFMT_ALPHA_INTENSITY_88    0xd
#define GR_TEXFMT_AP_88                 0xe /* 8-bit alpha 8-bit palette */
#define GR_TEXFMT_RSVD2                 0xf
#define GR_TEXFMT_RSVD4                 GR_TEXFMT_RSVD2

#define GR_TEXTABLE_NCC0                 0x0
#define GR_TEXTABLE_NCC1                 0x1
#define GR_TEXTABLE_PALETTE              0x2
#define GR_TEXTABLE_PALETTE_6666_EXT     0x3

#define GR_NCCTABLE_NCC0    0x0
#define GR_NCCTABLE_NCC1    0x1

#define GR_TEXBASE_256      0x3
#define GR_TEXBASE_128      0x2
#define GR_TEXBASE_64       0x1
#define GR_TEXBASE_32_TO_1  0x0

#define GR_MODE_DISABLE     0x0
#define GR_MODE_ENABLE      0x1

#define GR_AA_ORDERED            0x01
#define GR_ALLOW_MIPMAP_DITHER   0x02
#define GR_PASSTHRU              0x03
#define GR_SHAMELESS_PLUG        0x04
#define GR_VIDEO_SMOOTHING       0x05

#define GR_WINDOW_COORDS    0x00
#define GR_CLIP_COORDS      0x01

/* Types of data in strips */
#define GR_FLOAT        0
#define GR_U8           1

/* Parameters for strips */
#define GR_PARAM_XY       0x01
#define GR_PARAM_Z        0x02
#define GR_PARAM_W        0x03
#define GR_PARAM_Q        0x04
#define GR_PARAM_FOG_EXT  0x05

#define GR_PARAM_A        0x10

#define GR_PARAM_RGB      0x20

#define GR_PARAM_PARGB    0x30

#define GR_PARAM_ST0      0x40
#define GR_PARAM_ST1      GR_PARAM_ST0+1
#define GR_PARAM_ST2      GR_PARAM_ST0+2

#define GR_PARAM_Q0       0x50
#define GR_PARAM_Q1       GR_PARAM_Q0+1
#define GR_PARAM_Q2       GR_PARAM_Q0+2

#define GR_PARAM_DISABLE  0x00
#define GR_PARAM_ENABLE   0x01

/*
** grDrawVertexArray/grDrawVertexArrayContiguous primitive type
*/
#define GR_POINTS                        0
#define GR_LINE_STRIP                    1
#define GR_LINES                         2
#define GR_POLYGON                       3
#define GR_TRIANGLE_STRIP                GL_TRIANGLE_STRIP
#define GR_TRIANGLE_FAN                  GL_TRIANGLE_FAN
#define GR_TRIANGLES                     GL_TRIANGLES
#define GR_TRIANGLE_STRIP_CONTINUE       7
#define GR_TRIANGLE_FAN_CONTINUE         8

/* 
** grGet/grReset types
*/
#define GR_BITS_DEPTH                   0x01
#define GR_BITS_RGBA                    0x02
#define GR_FIFO_FULLNESS                0x03
#define GR_FOG_TABLE_ENTRIES            0x04
#define GR_GAMMA_TABLE_ENTRIES          0x05
#define GR_GLIDE_STATE_SIZE             0x06
#define GR_GLIDE_VERTEXLAYOUT_SIZE      0x07
#define GR_IS_BUSY                      0x08
#define GR_LFB_PIXEL_PIPE               0x09
#define GR_MAX_TEXTURE_SIZE             0x0a
#define GR_MAX_TEXTURE_ASPECT_RATIO     0x0b
#define GR_MEMORY_FB                    0x0c
#define GR_MEMORY_TMU                   0x0d
#define GR_MEMORY_UMA                   0x0e
#define GR_NUM_BOARDS                   0x0f
#define GR_NON_POWER_OF_TWO_TEXTURES    0x10
#define GR_NUM_FB                       0x11
#define GR_NUM_SWAP_HISTORY_BUFFER      0x12
#define GR_NUM_TMU                      0x13
#define GR_PENDING_BUFFERSWAPS          0x14
#define GR_REVISION_FB                  0x15
#define GR_REVISION_TMU                 0x16
#define GR_STATS_LINES                  0x17  /* grGet/grReset */
#define GR_STATS_PIXELS_AFUNC_FAIL      0x18
#define GR_STATS_PIXELS_CHROMA_FAIL     0x19
#define GR_STATS_PIXELS_DEPTHFUNC_FAIL  0x1a
#define GR_STATS_PIXELS_IN              0x1b
#define GR_STATS_PIXELS_OUT             0x1c
#define GR_STATS_PIXELS                 0x1d  /* grReset */
#define GR_STATS_POINTS                 0x1e  /* grGet/grReset */
#define GR_STATS_TRIANGLES_IN           0x1f
#define GR_STATS_TRIANGLES_OUT          0x20
#define GR_STATS_TRIANGLES              0x21  /* grReset */
#define GR_SWAP_HISTORY                 0x22
#define GR_SUPPORTS_PASSTHRU            0x23
#define GR_TEXTURE_ALIGN                0x24
#define GR_VIDEO_POSITION               0x25
#define GR_VIEWPORT                     0x26
#define GR_WDEPTH_MIN_MAX               0x27
#define GR_ZDEPTH_MIN_MAX               0x28
#define GR_VERTEX_PARAMETER             0x29
#define GR_BITS_GAMMA                   0x2a
#define GR_GET_RESERVED_1               0x1000

/*
** grGetString types
*/
#define GR_EXTENSION                    0xa0
#define GR_HARDWARE                     0xa1
#define GR_RENDERER                     0xa2
#define GR_VENDOR                       0xa3
#define GR_VERSION                      0xa4

/*
** -----------------------------------------------------------------------
** STRUCTURES
** -----------------------------------------------------------------------
*/

typedef struct {
    int32_t           smallLodLog2;
    int32_t           largeLodLog2;
    int32_t   aspectRatioLog2;
    int32_t format;
    int               width;
    int               height;
    void              *data;
} GrTexInfo;

#define GR_QUERY_ANY  ((uint32_t)(~0))

#define GR_LFB_SRC_FMT_565          0x00
#define GR_LFB_SRC_FMT_555          0x01
#define GR_LFB_SRC_FMT_1555         0x02
#define GR_LFB_SRC_FMT_888          0x04
#define GR_LFB_SRC_FMT_8888         0x05
#define GR_LFB_SRC_FMT_565_DEPTH    0x0c
#define GR_LFB_SRC_FMT_555_DEPTH    0x0d
#define GR_LFB_SRC_FMT_1555_DEPTH   0x0e
#define GR_LFB_SRC_FMT_ZA16         0x0f
#define GR_LFB_SRC_FMT_RLE16        0x80

#ifdef H3D
#define GR_HINT_H3DENABLE               4
#undef  GR_HINTTYPE_MAX
#define GR_HINTTYPE_MAX 4
#endif

/*
** -----------------------------------------------------------------------
** FUNCTION PROTOTYPES
** -----------------------------------------------------------------------
*/
#ifndef FX_GLIDE_NO_FUNC_PROTO
/*
** rendering functions
*/
void grDrawPoint( const void *pt );

void grDrawLine( const void *v1, const void *v2 );

void grVertexLayout(uint32_t param, int32_t offset, uint32_t mode);

void grDrawVertexArrayContiguous(uint32_t mode, uint32_t Count, void *pointers);

#define grBufferClear(color, alpha, depth) \
{ \
   glClearColor(0, 0, 0, 0); \
   glClearDepth(depth / 65535.0f); \
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); \
}

#define grBufferSwap(interval) retro_return(true)

/*
** error management
*/
typedef void (*GrErrorCallbackFnc_t)( const char *string, int32_t fatal );

void grErrorSetCallback( GrErrorCallbackFnc_t fnc );

/*
** SST routines
*/
uint32_t grSstWinOpen(void);

 int32_t 
grSstWinClose( uint32_t context );

/*
** Glide configuration and special effect maintenance functions
*/
#define grAlphaBlendFunction(rgb_sf, rgb_df, alpha_sf, alpha_df) glEnable(GL_BLEND); glBlendFuncSeparate(rgb_sf, rgb_df, alpha_sf, alpha_df)

void grAlphaCombine(
               int32_t function, int32_t factor,
               int32_t local, int32_t other,
               int32_t invert
               );

void  grAlphaTestFunction( int32_t function, uint8_t value, int set_alpha_ref);

void  grAlphaTestReferenceValue( uint8_t value );

void  grChromakeyMode( int32_t mode );

void grChromakeyValue( uint32_t value );

#define grClipWindow(minx, miny, maxx, maxy) glScissor(minx, height - maxy, maxx - minx, maxy - miny); glEnable(GL_SCISSOR_TEST)

void grColorCombine(
               int32_t function, int32_t factor,
               int32_t local, int32_t other,
               int32_t invert );

#define grColorMask(rgb, a) glColorMask(rgb, rgb, rgb, a)

void grCullMode( int32_t mode );

void grConstantColorValue( uint32_t value );

void grDepthBiasLevel( int32_t level );

#define grDepthBufferFunction(function) glDepthFunc(function)

#define grDepthBufferMode(mode) \
{ \
   if (mode == GR_DEPTHBUFFER_DISABLE) \
      glDisable(GL_DEPTH_TEST); \
   else \
      glEnable(GL_DEPTH_TEST); \
}

#define grDepthMask(mask) glDepthMask(mask)

void grFogMode( int32_t mode, uint32_t fogcolor );

void grLoadGammaTable( uint32_t nentries, uint32_t *red, uint32_t *green, uint32_t *blue);

void grDepthRange( float n, float f );

void grStippleMode( int32_t mode );

void grStipplePattern( uint32_t mode );

void grViewport( int32_t x, int32_t y, int32_t width, int32_t height );

/*
** texture mapping control functions
*/
 uint32_t  
grTexCalcMemRequired(
                    int32_t lodmax,
                     int32_t aspect, int32_t fmt);

#define TMU_SIZE (8 * 2048 * 2048)

#define grTexMaxAddress(tmu) ((TMU_SIZE * 2) - 1)

void grTexSource( int32_t tmu,
             uint32_t      startAddress,
             uint32_t      evenOdd,
             GrTexInfo  *info,
             int do_download);

void grTexFilterClampMode(
               int32_t tmu,
               int32_t s_clampmode,
               int32_t t_clampmode,
               int32_t minfilter_mode,
               int32_t magfilter_mode
               );

void grTexCombine(
             int32_t tmu,
             int32_t rgb_function,
             int32_t rgb_factor, 
             int32_t alpha_function,
             int32_t alpha_factor,
             int32_t rgb_invert,
             int32_t alpha_invert
             );

void grTexDetailControl(
                   int32_t tmu,
                   int lod_bias,
                   uint8_t detail_scale,
                   float detail_max
                   );

void grTexMipMapMode( int32_t     tmu, 
                 int32_t mode,
                 int32_t         lodBlend );

/*
** linear frame buffer functions
*/

 int32_t 
grLfbLock( int32_t type, int32_t buffer, int32_t writeMode,
           int32_t origin, int32_t pixelPipeline, 
           GrLfbInfo_t *info );

#define grLfbUnlock(type, buffer) (true)

void grLfbConstantAlpha( uint8_t alpha );

void grLfbConstantDepth( uint32_t depth );

void grLfbWriteColorSwizzle(int32_t swizzleBytes, int32_t swapWords);

void grLfbWriteColorFormat(int32_t colorFormat);

 int32_t 
grLfbWriteRegion( int32_t dst_buffer, 
                  uint32_t dst_x, uint32_t dst_y, 
                  uint32_t src_format, 
                  uint32_t src_width, uint32_t src_height, 
                  int32_t pixelPipeline,
                  int32_t src_stride, void *src_data );

 int32_t 
grLfbReadRegion( int32_t src_buffer,
                 uint32_t src_x, uint32_t src_y,
                 uint32_t src_width, uint32_t src_height,
                 uint32_t dst_stride, void *dst_data );

#define guFogGenerateLinear(nearZ, farZ) \
{ \
   fogStart = (nearZ) / 255.0f; \
   fogEnd = (farZ) / 255.0f; \
}

#endif /* FX_GLIDE_NO_FUNC_PROTO */

#ifdef __cplusplus
}
#endif

#endif /* __GLIDE_H__ */
