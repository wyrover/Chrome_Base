
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkAvoidXfermode_DEFINED
#define SkAvoidXfermode_DEFINED

#include "SkXfermode.h"

/** \class SkAvoidXfermode

    This xfermode will draw the src everywhere except on top of the specified
    color.
*/
class SkAvoidXfermode : public SkXfermode {
public:
    enum Mode {
        kAvoidColor_Mode,   //!< draw everywhere except on the opColor
        kTargetColor_Mode   //!< draw only on top of the opColor
    };

    /** This xfermode draws, or doesn't draw, based on the destination's
        distance from an op-color.

        There are two modes, and each mode interprets a tolerance value.

        Avoid: In this mode, drawing is allowed only on destination pixels that
               are different from the op-color.
               Tolerance near 0: avoid any colors even remotely similar to the op-color
               Tolerance near 255: avoid only colors nearly identical to the op-color

        Target: In this mode, drawing only occurs on destination pixels that
                are similar to the op-color
                Tolerance near 0: draw only on colors that are nearly identical to the op-color
                Tolerance near 255: draw on any colors even remotely similar to the op-color
     */
    SkAvoidXfermode(SkColor opColor, U8CPU tolerance, Mode mode);

    // overrides from SkXfermode
    virtual void xfer32(SkPMColor dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);
    virtual void xfer16(uint16_t dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);
    virtual void xfer4444(uint16_t dst[], const SkPMColor src[], int count,
                          const SkAlpha aa[]);
    virtual void xferA8(SkAlpha dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);

    // overrides from SkFlattenable
    virtual Factory getFactory();
    virtual void flatten(SkFlattenableWriteBuffer&);

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer) {
        return SkNEW_ARGS(SkAvoidXfermode, (buffer));
    }

protected:
    SkAvoidXfermode(SkFlattenableReadBuffer&);

private:
    SkColor     fOpColor;
    uint32_t    fDistMul;   // x.14
    Mode        fMode;

    static SkFlattenable* Create(SkFlattenableReadBuffer&);

    typedef SkXfermode INHERITED;
};

#endif
