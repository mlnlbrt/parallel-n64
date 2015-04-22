#ifndef GSP_H
#define GSP_H

#include <boolean.h>
#include "Types.h"
#include "GBI.h"
#include "gDP.h"

#define CHANGED_VIEWPORT        0x01
#define CHANGED_MATRIX          0x02
#define CHANGED_COLORBUFFER     0x04
#define CHANGED_GEOMETRYMODE    0x08
#define CHANGED_TEXTURE         0x10
#define CHANGED_FOGPOSITION     0x20
#define CHANGED_TEXTURESCALE    0x40

#define gSPFlushTriangles() \
if \
( \
    ( \
         (config.tribufferOpt) && \
         (OGL.triangles.num > 1000) || \
         ( \
             (__RSP.nextCmd != G_NOOP) && \
             (__RSP.nextCmd != G_RDPNOOP) && \
             (__RSP.nextCmd != G_MOVEMEM) && \
             (__RSP.nextCmd != G_ENDDL) && \
             (__RSP.nextCmd != G_DL) && \
             (__RSP.nextCmd != G_VTXCOLORBASE) && \
             (__RSP.nextCmd != G_TRI1) && \
             (__RSP.nextCmd != G_TRI2) && \
             (__RSP.nextCmd != G_TRI4) && \
             (__RSP.nextCmd != G_QUAD) && \
             (__RSP.nextCmd != G_VTX) && \
             (__RSP.nextCmd != G_MTX) \
         ) \
    ) || \
    ( \
        (__RSP.nextCmd != G_TRI1) && \
        (__RSP.nextCmd != G_TRI2) && \
        (__RSP.nextCmd != G_TRI4) && \
        (__RSP.nextCmd != G_QUAD) \
    ) \
) \
{ \
    OGL_DrawTriangles(); \
}


#define CLIP_X      0x03
#define CLIP_NEGX   0x01
#define CLIP_POSX   0x02

#define CLIP_Y      0x0C
#define CLIP_NEGY   0x04
#define CLIP_POSY   0x08

#define CLIP_Z      0x10

#define CLIP_ALL	0x1F // CLIP_NEGX|CLIP_POSX|CLIP_NEGY|CLIP_POSY|CLIP_Z

typedef struct
{
    f32     x, y, z, w;
    f32     nx, ny, nz, __pad0;
    f32     r, g, b, a;
    f32 flat_r, flat_g, flat_b, flat_a;
    f32     s, t;
    u8 HWLight;
    s16     flag;
    u32     clip;
} SPVertex;

typedef struct SPLight
{
	f32 r, g, b;
	f32 x, y, z;
	f32 posx, posy, posz, posw;
	f32 ca, la, qa;
} SPLight;

typedef SPVertex SPTriangle[3];

typedef struct
{
    u32 segment[16];

    struct
    {
        u32 modelViewi, stackSize, billboard;
        f32 modelView[32][4][4];
        f32 projection[4][4];
        f32 combined[4][4];
    } matrix;

    struct
    {
        f32 A, B, C, D;
        f32 X, Y;
        f32 baseScaleX, baseScaleY;
    } objMatrix;

    u32 objRendermode;

    u32 vertexColorBase;
    u32 vertexi;

    struct SPLight lights[12];
    SPLight lookat[2];
    bool lookatEnable;

    struct
    {
        f32 scales, scalet;
        s32 level, on, tile;
    } texture;

    gDPTile *textureTile[2];

    struct
    {
        f32 vscale[4];
        f32 vtrans[4];
        f32 x, y, width, height;
        f32 nearz, farz;
    } viewport;

    struct
    {
        s16 multiplier, offset;
    } fog;

    struct
    {
        u32 address, width, height, format, size, palette;
        f32 imageX, imageY, scaleW, scaleH;
    } bgImage;

    u32 geometryMode;
    s32 numLights;

    u32 changed;

    u32 status[4];

    struct
    {
       u32 vtx, mtx, tex_offset, tex_shift, tex_count;
    } DMAOffsets;

	// CBFD
	u32 vertexNormalBase;
	f32 vertexCoordMod[16];
} gSPInfo;

extern gSPInfo gSP;

void gSPLoadUcodeEx( u32 uc_start, u32 uc_dstart, u16 uc_dsize );
void gSPNoOp();
void gSPMatrix( u32 matrix, u8 param );
void gSPDMAMatrix( u32 matrix, u8 index, u8 multiply );
void gSPViewport( u32 v );
void gSPForceMatrix( u32 mptr );
void gSPLight( u32 l, s32 n );
void gSPLookAt( u32 _l, u32 _n );
void gSPVertex( u32 v, u32 n, u32 v0 );
void gSPCIVertex( u32 v, u32 n, u32 v0 );
void gSPDMAVertex( u32 v, u32 n, u32 v0 );
void gSPDisplayList( u32 dl );
void gSPDMADisplayList( u32 dl, u32 n );
void gSPBranchList( u32 dl );
void gSPBranchLessZ( u32 branchdl, u32 vtx, f32 zval );
void gSPSprite2DBase( u32 base );
void gSPDMATriangles( u32 tris, u32 n );
void gSP1Quadrangle( s32 v0, s32 v1, s32 v2, s32 v3 );
void gSPCullDisplayList( u32 v0, u32 vn );
void gSPPopMatrix( u32 param );
void gSPPopMatrixN( u32 param, u32 num );
void gSPSegment( s32 seg, s32 base );
void gSPClipRatio( u32 r );
void gSPInsertMatrix( u32 where, u32 num );
void gSPModifyVertex( u32 vtx, u32 where, u32 val );
void gSPNumLights( s32 n );
void gSPLightColor( u32 lightNum, u32 packedColor );
void gSPFogFactor( s16 fm, s16 fo );
void gSPPerspNormalize( u16 scale );
void gSPTexture( f32 sc, f32 tc, s32 level, s32 tile, s32 on );
void gSPEndDisplayList();
void gSPGeometryMode( u32 clear, u32 set );
void gSPSetGeometryMode( u32 mode );
void gSPClearGeometryMode( u32 mode );
void gSPLine3D( s32 v0, s32 v1, s32 flag );
void gSPLineW3D( s32 v0, s32 v1, s32 wd, s32 flag );
void gSPObjRectangle( u32 sp );
void gSPObjSprite( u32 sp );
void gSPObjLoadTxtr( u32 tx );
void gSPObjLoadTxSprite( u32 txsp );
void gSPObjLoadTxRectR( u32 txsp );
void gSPBgRect1Cyc( u32 bg );
void gSPBgRectCopy( u32 bg );
void gSPObjMatrix( u32 mtx );
void gSPObjSubMatrix( u32 mtx );
void gSPSetDMAOffsets( u32 mtxoffset, u32 vtxoffset );
void gSPSetVertexColorBase( u32 base );
void gSPProcessVertex(u32 v);

void gSPTriangleUnknown();

void gSP1Triangle(s32 v0, s32 v1, s32 v2);
void gSP2Triangles(const s32 v00, const s32 v01, const s32 v02, const s32 flag0,
                    const s32 v10, const s32 v11, const s32 v12, const s32 flag1 );
void gSP4Triangles(const s32 v00, const s32 v01, const s32 v02,
                    const s32 v10, const s32 v11, const s32 v12,
                    const s32 v20, const s32 v21, const s32 v22,
                    const s32 v30, const s32 v31, const s32 v32 );


extern void (*gSPTransformVertex)(float vtx[4], float mtx[4][4]);
extern void (*gSPLightVertex)(u32 v);
extern void (*gSPBillboardVertex)(u32 v, u32 i);

#endif

