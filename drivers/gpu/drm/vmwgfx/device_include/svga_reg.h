<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**********************************************************
 * Copyright 1998-2015 VMware, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person
 * obtaining a copy of this software and associated करोcumentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************/

/*
 * svga_reg.h --
 *
 *    Virtual hardware definitions क्रम the VMware SVGA II device.
 */

#अगर_अघोषित _SVGA_REG_H_
#घोषणा _SVGA_REG_H_
#समावेश <linux/pci_ids.h>

#घोषणा INCLUDE_ALLOW_MODULE
#घोषणा INCLUDE_ALLOW_USERLEVEL

#घोषणा INCLUDE_ALLOW_VMCORE
#समावेश "includeCheck.h"

#समावेश "svga_types.h"

/*
 * SVGA_REG_ENABLE bit definitions.
 */
प्रकार क्रमागत अणु
   SVGA_REG_ENABLE_DISABLE = 0,
   SVGA_REG_ENABLE_ENABLE = (1 << 0),
   SVGA_REG_ENABLE_HIDE = (1 << 1),
पूर्ण SvgaRegEnable;

प्रकार uपूर्णांक32 SVGAMobId;

/*
 * Arbitrary and meaningless limits. Please ignore these when writing
 * new drivers.
 */
#घोषणा SVGA_MAX_WIDTH                  2560
#घोषणा SVGA_MAX_HEIGHT                 1600


#घोषणा SVGA_MAX_BITS_PER_PIXEL         32
#घोषणा SVGA_MAX_DEPTH                  24
#घोषणा SVGA_MAX_DISPLAYS               10
#घोषणा SVGA_MAX_SCREEN_SIZE            8192
#घोषणा SVGA_SCREEN_ROOT_LIMIT (SVGA_MAX_SCREEN_SIZE * SVGA_MAX_DISPLAYS)


/*
 * Legal values क्रम the SVGA_REG_CURSOR_ON रेजिस्टर in old-fashioned
 * cursor bypass mode.
 */
#घोषणा SVGA_CURSOR_ON_HIDE            0x0
#घोषणा SVGA_CURSOR_ON_SHOW            0x1

/*
 * Remove the cursor from the framebuffer
 * because we need to see what's under it
 */
#घोषणा SVGA_CURSOR_ON_REMOVE_FROM_FB  0x2

/* Put the cursor back in the framebuffer so the user can see it */
#घोषणा SVGA_CURSOR_ON_RESTORE_TO_FB   0x3

/*
 * The maximum framebuffer size that can traced क्रम guests unless the
 * SVGA_CAP_GBOBJECTS is set in SVGA_REG_CAPABILITIES.  In that हाल
 * the full framebuffer can be traced independent of this limit.
 */
#घोषणा SVGA_FB_MAX_TRACEABLE_SIZE      0x1000000

#घोषणा SVGA_MAX_PSEUDOCOLOR_DEPTH      8
#घोषणा SVGA_MAX_PSEUDOCOLORS           (1 << SVGA_MAX_PSEUDOCOLOR_DEPTH)
#घोषणा SVGA_NUM_PALETTE_REGS           (3 * SVGA_MAX_PSEUDOCOLORS)

#घोषणा SVGA_MAGIC         0x900000UL
#घोषणा SVGA_MAKE_ID(ver)  (SVGA_MAGIC << 8 | (ver))

/* Version 2 let the address of the frame buffer be अचिन्हित on Win32 */
#घोषणा SVGA_VERSION_2     2
#घोषणा SVGA_ID_2          SVGA_MAKE_ID(SVGA_VERSION_2)

/* Version 1 has new रेजिस्टरs starting with SVGA_REG_CAPABILITIES so
   PALETTE_BASE has moved */
#घोषणा SVGA_VERSION_1     1
#घोषणा SVGA_ID_1          SVGA_MAKE_ID(SVGA_VERSION_1)

/* Version 0 is the initial version */
#घोषणा SVGA_VERSION_0     0
#घोषणा SVGA_ID_0          SVGA_MAKE_ID(SVGA_VERSION_0)

/*
 * "Invalid" value क्रम all SVGA IDs.
 * (Version ID, screen object ID, surface ID...)
 */
#घोषणा SVGA_ID_INVALID    0xFFFFFFFF

/* Port offsets, relative to BAR0 */
#घोषणा SVGA_INDEX_PORT         0x0
#घोषणा SVGA_VALUE_PORT         0x1
#घोषणा SVGA_BIOS_PORT          0x2
#घोषणा SVGA_IRQSTATUS_PORT     0x8

/*
 * Interrupt source flags क्रम IRQSTATUS_PORT and IRQMASK.
 *
 * Interrupts are only supported when the
 * SVGA_CAP_IRQMASK capability is present.
 */
#घोषणा SVGA_IRQFLAG_ANY_FENCE            0x1    /* Any fence was passed */
#घोषणा SVGA_IRQFLAG_FIFO_PROGRESS        0x2    /* Made क्रमward progress in the FIFO */
#घोषणा SVGA_IRQFLAG_FENCE_GOAL           0x4    /* SVGA_FIFO_FENCE_GOAL reached */
#घोषणा SVGA_IRQFLAG_COMMAND_BUFFER       0x8    /* Command buffer completed */
#घोषणा SVGA_IRQFLAG_ERROR                0x10   /* Error जबतक processing commands */

/*
 * The byte-size is the size of the actual cursor data,
 * possibly after expanding it to the current bit depth.
 *
 * 40K is sufficient memory क्रम two 32-bit planes क्रम a 64 x 64 cursor.
 *
 * The dimension limit is a bound on the maximum width or height.
 */
#घोषणा SVGA_MAX_CURSOR_CMD_BYTES  (40 * 1024)
#घोषणा SVGA_MAX_CURSOR_CMD_DIMENSION 1024

/*
 * Registers
 */

क्रमागत अणु
   SVGA_REG_ID = 0,
   SVGA_REG_ENABLE = 1,
   SVGA_REG_WIDTH = 2,
   SVGA_REG_HEIGHT = 3,
   SVGA_REG_MAX_WIDTH = 4,
   SVGA_REG_MAX_HEIGHT = 5,
   SVGA_REG_DEPTH = 6,
   SVGA_REG_BITS_PER_PIXEL = 7,       /* Current bpp in the guest */
   SVGA_REG_PSEUDOCOLOR = 8,
   SVGA_REG_RED_MASK = 9,
   SVGA_REG_GREEN_MASK = 10,
   SVGA_REG_BLUE_MASK = 11,
   SVGA_REG_BYTES_PER_LINE = 12,
   SVGA_REG_FB_START = 13,            /* (Deprecated) */
   SVGA_REG_FB_OFFSET = 14,
   SVGA_REG_VRAM_SIZE = 15,
   SVGA_REG_FB_SIZE = 16,

   /* ID 0 implementation only had the above रेजिस्टरs, then the palette */
   SVGA_REG_ID_0_TOP = 17,

   SVGA_REG_CAPABILITIES = 17,
   SVGA_REG_MEM_START = 18,           /* (Deprecated) */
   SVGA_REG_MEM_SIZE = 19,
   SVGA_REG_CONFIG_DONE = 20,         /* Set when memory area configured */
   SVGA_REG_SYNC = 21,                /* See "FIFO Synchronization Registers" */
   SVGA_REG_BUSY = 22,                /* See "FIFO Synchronization Registers" */
   SVGA_REG_GUEST_ID = 23,            /* (Deprecated) */
   SVGA_REG_DEAD = 24,                /* Drivers should never ग_लिखो this. */
   SVGA_REG_CURSOR_X = 25,            /* (Deprecated) */
   SVGA_REG_CURSOR_Y = 26,            /* (Deprecated) */
   SVGA_REG_CURSOR_ON = 27,           /* (Deprecated) */
   SVGA_REG_HOST_BITS_PER_PIXEL = 28, /* (Deprecated) */
   SVGA_REG_SCRATCH_SIZE = 29,        /* Number of scratch रेजिस्टरs */
   SVGA_REG_MEM_REGS = 30,            /* Number of FIFO रेजिस्टरs */
   SVGA_REG_NUM_DISPLAYS = 31,        /* (Deprecated) */
   SVGA_REG_PITCHLOCK = 32,           /* Fixed pitch क्रम all modes */
   SVGA_REG_IRQMASK = 33,             /* Interrupt mask */

   /* Legacy multi-monitor support */
   SVGA_REG_NUM_GUEST_DISPLAYS = 34,/* Number of guest displays in X/Y direction */
   SVGA_REG_DISPLAY_ID = 35,        /* Display ID क्रम the following display attributes */
   SVGA_REG_DISPLAY_IS_PRIMARY = 36,/* Whether this is a primary display */
   SVGA_REG_DISPLAY_POSITION_X = 37,/* The display position x */
   SVGA_REG_DISPLAY_POSITION_Y = 38,/* The display position y */
   SVGA_REG_DISPLAY_WIDTH = 39,     /* The display's width */
   SVGA_REG_DISPLAY_HEIGHT = 40,    /* The display's height */

   /* See "Guest memory regions" below. */
   SVGA_REG_GMR_ID = 41,
   SVGA_REG_GMR_DESCRIPTOR = 42,
   SVGA_REG_GMR_MAX_IDS = 43,
   SVGA_REG_GMR_MAX_DESCRIPTOR_LENGTH = 44,

   SVGA_REG_TRACES = 45,            /* Enable trace-based updates even when FIFO is on */
   SVGA_REG_GMRS_MAX_PAGES = 46,    /* Maximum number of 4KB pages क्रम all GMRs */
   SVGA_REG_MEMORY_SIZE = 47,       /* Total dedicated device memory excluding FIFO */
   SVGA_REG_COMMAND_LOW = 48,       /* Lower 32 bits and submits commands */
   SVGA_REG_COMMAND_HIGH = 49,      /* Upper 32 bits of command buffer PA */

   /*
    * Max primary memory.
    * See SVGA_CAP_NO_BB_RESTRICTION.
    */
   SVGA_REG_MAX_PRIMARY_MEM = 50,
   SVGA_REG_MAX_PRIMARY_BOUNDING_BOX_MEM = 50,

   /*
    * Legacy version of SVGA_REG_GBOBJECT_MEM_SIZE_KB क्रम drivers that
    * करोn't know how to convert to a 64-bit byte value without overflowing.
    * (See SVGA_REG_GBOBJECT_MEM_SIZE_KB).
    */
   SVGA_REG_SUGGESTED_GBOBJECT_MEM_SIZE_KB = 51,

   SVGA_REG_DEV_CAP = 52,           /* Write dev cap index, पढ़ो value */
   SVGA_REG_CMD_PREPEND_LOW = 53,
   SVGA_REG_CMD_PREPEND_HIGH = 54,
   SVGA_REG_SCREENTARGET_MAX_WIDTH = 55,
   SVGA_REG_SCREENTARGET_MAX_HEIGHT = 56,
   SVGA_REG_MOB_MAX_SIZE = 57,
   SVGA_REG_BLANK_SCREEN_TARGETS = 58,
   SVGA_REG_CAP2 = 59,
   SVGA_REG_DEVEL_CAP = 60,

   /*
    * Allow the guest to hपूर्णांक to the device which driver is running.
    *
    * This should not generally change device behavior, but might be
    * convenient to work-around specअगरic bugs in guest drivers.
    *
    * Drivers should first ग_लिखो their id value पूर्णांकo SVGA_REG_GUEST_DRIVER_ID,
    * and then fill out all of the version रेजिस्टरs that they have defined.
    *
    * After the driver has written all of the रेजिस्टरs, they should
    * then ग_लिखो the value SVGA_REG_GUEST_DRIVER_ID_SUBMIT to the
    * SVGA_REG_GUEST_DRIVER_ID रेजिस्टर, to संकेत that they have finished.
    *
    * The SVGA_REG_GUEST_DRIVER_ID values are defined below by the
    * SVGARegGuestDriverId क्रमागत.
    *
    * The SVGA_REG_GUEST_DRIVER_VERSION fields are driver-specअगरic,
    * but ideally should encode a monotonically increasing number that allows
    * the device to perक्रमm inequality checks against ranges of driver versions.
    */
   SVGA_REG_GUEST_DRIVER_ID = 61,
   SVGA_REG_GUEST_DRIVER_VERSION1 = 62,
   SVGA_REG_GUEST_DRIVER_VERSION2 = 63,
   SVGA_REG_GUEST_DRIVER_VERSION3 = 64,
   SVGA_REG_CURSOR_MOBID = 65,
   SVGA_REG_CURSOR_MAX_BYTE_SIZE = 66,
   SVGA_REG_CURSOR_MAX_DIMENSION = 67,

   SVGA_REG_FIFO_CAPS = 68,
   SVGA_REG_FENCE = 69,

   SVGA_REG_RESERVED1 = 70,
   SVGA_REG_RESERVED2 = 71,
   SVGA_REG_RESERVED3 = 72,
   SVGA_REG_RESERVED4 = 73,
   SVGA_REG_RESERVED5 = 74,
   SVGA_REG_SCREENDMA = 75,

   /*
    * The maximum amount of guest-backed objects that the device can have
    * resident at a समय. Guest-drivers should keep their working set size
    * below this limit क्रम best perक्रमmance.
    *
    * Note that this value is in kilobytes, and not bytes, because the actual
    * number of bytes might be larger than can fit in a 32-bit रेजिस्टर.
    *
    * PLEASE USE A 64-BIT VALUE WHEN CONVERTING THIS INTO BYTES.
    * (See SVGA_REG_SUGGESTED_GBOBJECT_MEM_SIZE_KB).
    */
   SVGA_REG_GBOBJECT_MEM_SIZE_KB = 76,

   SVGA_REG_TOP = 77,               /* Must be 1 more than the last रेजिस्टर */

   SVGA_PALETTE_BASE = 1024,        /* Base of SVGA color map */
   /* Next 768 (== 256*3) रेजिस्टरs exist क्रम colormap */
   SVGA_SCRATCH_BASE = SVGA_PALETTE_BASE + SVGA_NUM_PALETTE_REGS
                                    /* Base of scratch रेजिस्टरs */
   /* Next reg[SVGA_REG_SCRATCH_SIZE] रेजिस्टरs exist क्रम scratch usage:
      First 4 are reserved क्रम VESA BIOS Extension; any reमुख्यing are क्रम
      the use of the current SVGA driver. */
पूर्ण;


/*
 * Values क्रम SVGA_REG_GUEST_DRIVER_ID.
 */
प्रकार क्रमागत SVGARegGuestDriverId अणु
   SVGA_REG_GUEST_DRIVER_ID_UNKNOWN = 0,
   SVGA_REG_GUEST_DRIVER_ID_WDDM    = 1,
   SVGA_REG_GUEST_DRIVER_ID_LINUX   = 2,
   SVGA_REG_GUEST_DRIVER_ID_MAX,

   SVGA_REG_GUEST_DRIVER_ID_SUBMIT  = MAX_UINT32,
पूर्ण SVGARegGuestDriverId;


/*
 * Guest memory regions (GMRs):
 *
 * This is a new memory mapping feature available in SVGA devices
 * which have the SVGA_CAP_GMR bit set. Previously, there were two
 * fixed memory regions available with which to share data between the
 * device and the driver: the FIFO ('MEM') and the framebuffer. GMRs
 * are our name क्रम an extensible way of providing arbitrary DMA
 * buffers क्रम use between the driver and the SVGA device. They are a
 * new alternative to framebuffer memory, usable क्रम both 2D and 3D
 * graphics operations.
 *
 * Since GMR mapping must be करोne synchronously with guest CPU
 * execution, we use a new pair of SVGA रेजिस्टरs:
 *
 *   SVGA_REG_GMR_ID --
 *
 *     Read/ग_लिखो.
 *     This रेजिस्टर holds the 32-bit ID (a small positive पूर्णांकeger)
 *     of a GMR to create, delete, or redefine. Writing this रेजिस्टर
 *     has no side-effects.
 *
 *   SVGA_REG_GMR_DESCRIPTOR --
 *
 *     Write-only.
 *     Writing this रेजिस्टर will create, delete, or redefine the GMR
 *     specअगरied by the above ID रेजिस्टर. If this रेजिस्टर is zero,
 *     the GMR is deleted. Any poपूर्णांकers पूर्णांकo this GMR (including those
 *     currently being processed by FIFO commands) will be
 *     synchronously invalidated.
 *
 *     If this रेजिस्टर is nonzero, it must be the physical page
 *     number (PPN) of a data काष्ठाure which describes the physical
 *     layout of the memory region this GMR should describe. The
 *     descriptor काष्ठाure will be पढ़ो synchronously by the SVGA
 *     device when this रेजिस्टर is written. The descriptor need not
 *     reमुख्य allocated क्रम the lअगरeसमय of the GMR.
 *
 *     The guest driver should ग_लिखो SVGA_REG_GMR_ID first, then
 *     SVGA_REG_GMR_DESCRIPTOR.
 *
 *   SVGA_REG_GMR_MAX_IDS --
 *
 *     Read-only.
 *     The SVGA device may choose to support a maximum number of
 *     user-defined GMR IDs. This रेजिस्टर holds the number of supported
 *     IDs. (The maximum supported ID plus 1)
 *
 *   SVGA_REG_GMR_MAX_DESCRIPTOR_LENGTH --
 *
 *     Read-only.
 *     The SVGA device may choose to put a limit on the total number
 *     of SVGAGuestMemDescriptor काष्ठाures it will पढ़ो when defining
 *     a single GMR.
 *
 * The descriptor काष्ठाure is an array of SVGAGuestMemDescriptor
 * काष्ठाures. Each काष्ठाure may करो one of three things:
 *
 *   - Terminate the GMR descriptor list.
 *     (ppn==0, numPages==0)
 *
 *   - Add a PPN or range of PPNs to the GMR's भव address space.
 *     (ppn != 0, numPages != 0)
 *
 *   - Provide the PPN of the next SVGAGuestMemDescriptor, in order to
 *     support multi-page GMR descriptor tables without क्रमcing the
 *     driver to allocate physically contiguous memory.
 *     (ppn != 0, numPages == 0)
 *
 * Note that each physical page of SVGAGuestMemDescriptor काष्ठाures
 * can describe at least 2MB of guest memory. If the driver needs to
 * use more than one page of descriptor काष्ठाures, it must use one of
 * its SVGAGuestMemDescriptors to poपूर्णांक to an additional page.  The
 * device will never स्वतःmatically cross a page boundary.
 *
 * Once the driver has described a GMR, it is immediately available
 * क्रम use via any FIFO command that uses an SVGAGuestPtr काष्ठाure.
 * These poपूर्णांकers include a GMR identअगरier plus an offset पूर्णांकo that
 * GMR.
 *
 * The driver must check the SVGA_CAP_GMR bit beक्रमe using the GMR
 * रेजिस्टरs.
 */

/*
 * Special GMR IDs, allowing SVGAGuestPtrs to poपूर्णांक to framebuffer
 * memory as well.  In the future, these IDs could even be used to
 * allow legacy memory regions to be redefined by the guest as GMRs.
 *
 * Using the guest framebuffer (GFB) at BAR1 क्रम general purpose DMA
 * is being phased out. Please try to use user-defined GMRs whenever
 * possible.
 */
#घोषणा SVGA_GMR_शून्य         ((uपूर्णांक32) -1)
#घोषणा SVGA_GMR_FRAMEBUFFER  ((uपूर्णांक32) -2)  /* Guest Framebuffer (GFB) */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGAGuestMemDescriptor अणु
   uपूर्णांक32 ppn;
   uपूर्णांक32 numPages;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAGuestMemDescriptor;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGAGuestPtr अणु
   uपूर्णांक32 gmrId;
   uपूर्णांक32 offset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAGuestPtr;

/*
 * Register based command buffers --
 *
 * Provide an SVGA device पूर्णांकerface that allows the guest to submit
 * command buffers to the SVGA device through an SVGA device रेजिस्टर.
 * The metadata क्रम each command buffer is contained in the
 * SVGACBHeader काष्ठाure aदीर्घ with the वापस status codes.
 *
 * The SVGA device supports command buffers अगर
 * SVGA_CAP_COMMAND_BUFFERS is set in the device caps रेजिस्टर.  The
 * fअगरo must be enabled क्रम command buffers to be submitted.
 *
 * Command buffers are submitted when the guest writing the 64 byte
 * aligned physical address पूर्णांकo the SVGA_REG_COMMAND_LOW and
 * SVGA_REG_COMMAND_HIGH.  SVGA_REG_COMMAND_HIGH contains the upper 32
 * bits of the physical address.  SVGA_REG_COMMAND_LOW contains the
 * lower 32 bits of the physical address, since the command buffer
 * headers are required to be 64 byte aligned the lower 6 bits are
 * used क्रम the SVGACBContext value.  Writing to SVGA_REG_COMMAND_LOW
 * submits the command buffer to the device and queues it क्रम
 * execution.  The SVGA device supports at least
 * SVGA_CB_MAX_QUEUED_PER_CONTEXT command buffers that can be queued
 * per context and अगर that limit is reached the device will ग_लिखो the
 * status SVGA_CB_STATUS_QUEUE_FULL to the status value of the command
 * buffer header synchronously and not उठाओ any IRQs.
 *
 * It is invalid to submit a command buffer without a valid physical
 * address and results are undefined.
 *
 * The device guarantees that command buffers of size SVGA_CB_MAX_SIZE
 * will be supported.  If a larger command buffer is submitted results
 * are unspecअगरied and the device will either complete the command
 * buffer or वापस an error.
 *
 * The device guarantees that any inभागidual command in a command
 * buffer can be up to SVGA_CB_MAX_COMMAND_SIZE in size which is
 * enough to fit a 64x64 color-cursor definition.  If the command is
 * too large the device is allowed to process the command or वापस an
 * error.
 *
 * The device context is a special SVGACBContext that allows क्रम
 * synchronous रेजिस्टर like accesses with the flexibility of
 * commands.  There is a dअगरferent command set defined by
 * SVGADeviceContextCmdId.  The commands in each command buffer is not
 * allowed to straddle physical pages.
 *
 * The offset field which is available starting with the
 * SVGA_CAP_CMD_BUFFERS_2 cap bit can be set by the guest to bias the
 * start of command processing पूर्णांकo the buffer.  If an error is
 * encountered the errorOffset will still be relative to the specअगरic
 * PA, not biased by the offset.  When the command buffer is finished
 * the guest should not पढ़ो the offset field as there is no guarantee
 * what it will set to.
 *
 * When the SVGA_CAP_HP_CMD_QUEUE cap bit is set a new command queue
 * SVGA_CB_CONTEXT_1 is available.  Commands submitted to this queue
 * will be executed as quickly as possible by the SVGA device
 * potentially beक्रमe alपढ़ोy queued commands on SVGA_CB_CONTEXT_0.
 * The SVGA device guarantees that any command buffers submitted to
 * SVGA_CB_CONTEXT_0 will be executed after any _alपढ़ोy_ submitted
 * command buffers to SVGA_CB_CONTEXT_1.
 */

#घोषणा SVGA_CB_MAX_SIZE (512 * 1024)  /* 512 KB */
#घोषणा SVGA_CB_MAX_QUEUED_PER_CONTEXT 32
#घोषणा SVGA_CB_MAX_COMMAND_SIZE (32 * 1024) /* 32 KB */

#घोषणा SVGA_CB_CONTEXT_MASK 0x3f
प्रकार क्रमागत अणु
   SVGA_CB_CONTEXT_DEVICE = 0x3f,
   SVGA_CB_CONTEXT_0      = 0x0,
   SVGA_CB_CONTEXT_1      = 0x1, /* Supported with SVGA_CAP_HP_CMD_QUEUE */
   SVGA_CB_CONTEXT_MAX    = 0x2,
पूर्ण SVGACBContext;


प्रकार क्रमागत अणु
   /*
    * The guest is supposed to ग_लिखो SVGA_CB_STATUS_NONE to the status
    * field beक्रमe submitting the command buffer header, the host will
    * change the value when it is करोne with the command buffer.
    */
   SVGA_CB_STATUS_NONE             = 0,

   /*
    * Written by the host when a command buffer completes successfully.
    * The device उठाओs an IRQ with SVGA_IRQFLAG_COMMAND_BUFFER unless
    * the SVGA_CB_FLAG_NO_IRQ flag is set.
    */
   SVGA_CB_STATUS_COMPLETED        = 1,

   /*
    * Written by the host synchronously with the command buffer
    * submission to indicate the command buffer was not submitted.  No
    * IRQ is उठाओd.
    */
   SVGA_CB_STATUS_QUEUE_FULL       = 2,

   /*
    * Written by the host when an error was detected parsing a command
    * in the command buffer, errorOffset is written to contain the
    * offset to the first byte of the failing command.  The device
    * उठाओs the IRQ with both SVGA_IRQFLAG_ERROR and
    * SVGA_IRQFLAG_COMMAND_BUFFER.  Some of the commands may have been
    * processed.
    */
   SVGA_CB_STATUS_COMMAND_ERROR    = 3,

   /*
    * Written by the host अगर there is an error parsing the command
    * buffer header.  The device उठाओs the IRQ with both
    * SVGA_IRQFLAG_ERROR and SVGA_IRQFLAG_COMMAND_BUFFER.  The device
    * did not processes any of the command buffer.
    */
   SVGA_CB_STATUS_CB_HEADER_ERROR  = 4,

   /*
    * Written by the host अगर the guest requested the host to preempt
    * the command buffer.  The device will not उठाओ any IRQs and the
    * command buffer was not processed.
    */
   SVGA_CB_STATUS_PREEMPTED        = 5,

   /*
    * Written by the host synchronously with the command buffer
    * submission to indicate the the command buffer was not submitted
    * due to an error.  No IRQ is उठाओd.
    */
   SVGA_CB_STATUS_SUBMISSION_ERROR = 6,

   /*
    * Written by the host when the host finished a
    * SVGA_DC_CMD_ASYNC_STOP_QUEUE request क्रम this command buffer
    * queue.  The offset of the first byte not processed is stored in
    * the errorOffset field of the command buffer header.  All guest
    * visible side effects of commands till that poपूर्णांक are guaranteed
    * to be finished beक्रमe this is written.  The
    * SVGA_IRQFLAG_COMMAND_BUFFER IRQ is उठाओd as दीर्घ as the
    * SVGA_CB_FLAG_NO_IRQ is not set.
    */
   SVGA_CB_STATUS_PARTIAL_COMPLETE = 7,
पूर्ण SVGACBStatus;

प्रकार क्रमागत अणु
   SVGA_CB_FLAG_NONE       = 0,
   SVGA_CB_FLAG_NO_IRQ     = 1 << 0,
   SVGA_CB_FLAG_DX_CONTEXT = 1 << 1,
   SVGA_CB_FLAG_MOB        = 1 << 2,
पूर्ण SVGACBFlags;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   अस्थिर SVGACBStatus status; /* Modअगरied by device. */
   अस्थिर uपूर्णांक32 errorOffset;  /* Modअगरied by device. */
   uपूर्णांक64 id;
   SVGACBFlags flags;
   uपूर्णांक32 length;
   जोड़ अणु
      PA pa;
      काष्ठा अणु
         SVGAMobId mobid;
         uपूर्णांक32 mobOffset;
      पूर्ण mob;
   पूर्ण ptr;
   uपूर्णांक32 offset; /* Valid अगर CMD_BUFFERS_2 cap set, must be zero otherwise,
                   * modअगरied by device.
                   */
   uपूर्णांक32 dxContext; /* Valid अगर DX_CONTEXT flag set, must be zero otherwise */
   uपूर्णांक32 mustBeZero[6];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACBHeader;

प्रकार क्रमागत अणु
   SVGA_DC_CMD_NOP                   = 0,
   SVGA_DC_CMD_START_STOP_CONTEXT    = 1,
   SVGA_DC_CMD_PREEMPT               = 2,
   SVGA_DC_CMD_START_QUEUE           = 3, /* Requires SVGA_CAP_HP_CMD_QUEUE */
   SVGA_DC_CMD_ASYNC_STOP_QUEUE      = 4, /* Requires SVGA_CAP_HP_CMD_QUEUE */
   SVGA_DC_CMD_EMPTY_CONTEXT_QUEUE   = 5, /* Requires SVGA_CAP_HP_CMD_QUEUE */
   SVGA_DC_CMD_MAX                   = 6,
पूर्ण SVGADeviceContextCmdId;

/*
 * Starts or stops both SVGA_CB_CONTEXT_0 and SVGA_CB_CONTEXT_1.
 */

प्रकार काष्ठा SVGADCCmdStartStop अणु
   uपूर्णांक32 enable;
   SVGACBContext context; /* Must be zero */
पूर्ण SVGADCCmdStartStop;

/*
 * SVGADCCmdPreempt --
 *
 * This command allows the guest to request that all command buffers
 * on SVGA_CB_CONTEXT_0 be preempted that can be.  After execution
 * of this command all command buffers that were preempted will
 * alपढ़ोy have SVGA_CB_STATUS_PREEMPTED written पूर्णांकo the status
 * field.  The device might still be processing a command buffer,
 * assuming execution of it started beक्रमe the preemption request was
 * received.  Specअगरying the ignoreIDZero flag to TRUE will cause the
 * device to not preempt command buffers with the id field in the
 * command buffer header set to zero.
 */

प्रकार काष्ठा SVGADCCmdPreempt अणु
   SVGACBContext context; /* Must be zero */
   uपूर्णांक32 ignoreIDZero;
पूर्ण SVGADCCmdPreempt;

/*
 * Starts the requested command buffer processing queue.  Valid only
 * अगर the SVGA_CAP_HP_CMD_QUEUE cap is set.
 *
 * For a command queue to be considered runnable it must be enabled
 * and any corresponding higher priority queues must also be enabled.
 * For example in order क्रम command buffers to be processed on
 * SVGA_CB_CONTEXT_0 both SVGA_CB_CONTEXT_0 and SVGA_CB_CONTEXT_1 must
 * be enabled.  But क्रम commands to be runnable on SVGA_CB_CONTEXT_1
 * only that queue must be enabled.
 */

प्रकार काष्ठा SVGADCCmdStartQueue अणु
   SVGACBContext context;
पूर्ण SVGADCCmdStartQueue;

/*
 * Requests the SVGA device to stop processing the requested command
 * buffer queue as soon as possible.  The guest knows the stop has
 * completed when one of the following happens.
 *
 * 1) A command buffer status of SVGA_CB_STATUS_PARTIAL_COMPLETE is वापसed
 * 2) A command buffer error is encountered with would stop the queue
 *    regardless of the async stop request.
 * 3) All command buffers that have been submitted complete successfully.
 * 4) The stop completes synchronously अगर no command buffers are
 *    active on the queue when it is issued.
 *
 * If the command queue is not in a runnable state there is no
 * guarentee this async stop will finish.  For instance अगर the high
 * priority queue is not enabled and a stop is requested on the low
 * priority queue, the high priority queue must be reenabled to
 * guarantee that the async stop will finish.
 *
 * This command aदीर्घ with SVGA_DC_CMD_EMPTY_CONTEXT_QUEUE can be used
 * to implement mid command buffer preemption.
 *
 * Valid only अगर the SVGA_CAP_HP_CMD_QUEUE cap is set.
 */

प्रकार काष्ठा SVGADCCmdAsyncStopQueue अणु
   SVGACBContext context;
पूर्ण SVGADCCmdAsyncStopQueue;

/*
 * Requests the SVGA device to throw away any full command buffers on
 * the requested command queue that have not been started.  For a
 * driver to know which command buffers were thrown away a driver
 * should only issue this command when the queue is stopped, क्रम
 * whatever reason.
 */

प्रकार काष्ठा SVGADCCmdEmptyQueue अणु
   SVGACBContext context;
पूर्ण SVGADCCmdEmptyQueue;


/*
 * SVGAGMRImageFormat --
 *
 *    This is a packed representation of the source 2D image क्रमmat
 *    क्रम a GMR-to-screen blit. Currently it is defined as an encoding
 *    of the screen's color depth and bits-per-pixel, however, 16 bits
 *    are reserved क्रम future use to identअगरy other encodings (such as
 *    RGBA or higher-precision images).
 *
 *    Currently supported क्रमmats:
 *
 *       bpp depth  Format Name
 *       --- -----  -----------
 *        32    24  32-bit BGRX
 *        24    24  24-bit BGR
 *        16    16  RGB 5-6-5
 *        16    15  RGB 5-5-5
 *
 */

प्रकार काष्ठा SVGAGMRImageFormat अणु
   जोड़ अणु
      काष्ठा अणु
         uपूर्णांक32 bitsPerPixel : 8;
         uपूर्णांक32 colorDepth   : 8;
         uपूर्णांक32 reserved     : 16;  /* Must be zero */
      पूर्ण;

      uपूर्णांक32 value;
   पूर्ण;
पूर्ण SVGAGMRImageFormat;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGAGuestImage अणु
   SVGAGuestPtr         ptr;

   /*
    * A note on पूर्णांकerpretation of pitch: This value of pitch is the
    * number of bytes between vertically adjacent image
    * blocks. Normally this is the number of bytes between the first
    * pixel of two adjacent scanlines. With compressed textures,
    * however, this may represent the number of bytes between
    * compression blocks rather than between rows of pixels.
    *
    * XXX: Compressed textures currently must be tightly packed in guest memory.
    *
    * If the image is 1-dimensional, pitch is ignored.
    *
    * If 'pitch' is zero, the SVGA3D device calculates a pitch value
    * assuming each row of blocks is tightly packed.
    */
   uपूर्णांक32 pitch;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAGuestImage;

/*
 * SVGAColorBGRX --
 *
 *    A 24-bit color क्रमmat (BGRX), which करोes not depend on the
 *    क्रमmat of the legacy guest framebuffer (GFB) or the current
 *    GMRFB state.
 */

प्रकार काष्ठा SVGAColorBGRX अणु
   जोड़ अणु
      काष्ठा अणु
         uपूर्णांक32 b : 8;
         uपूर्णांक32 g : 8;
         uपूर्णांक32 r : 8;
	 uपूर्णांक32 x : 8;  /* Unused */
      पूर्ण;

      uपूर्णांक32 value;
   पूर्ण;
पूर्ण SVGAColorBGRX;


/*
 * SVGASignedRect --
 * SVGASignedPoपूर्णांक --
 *
 *    Signed rectangle and poपूर्णांक primitives. These are used by the new
 *    2D primitives क्रम drawing to Screen Objects, which can occupy a
 *    चिन्हित भव coordinate space.
 *
 *    SVGASignedRect specअगरies a half-खोलो पूर्णांकerval: the (left, top)
 *    pixel is part of the rectangle, but the (right, bottom) pixel is
 *    not.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   पूर्णांक32  left;
   पूर्णांक32  top;
   पूर्णांक32  right;
   पूर्णांक32  bottom;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGASignedRect;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   पूर्णांक32  x;
   पूर्णांक32  y;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGASignedPoपूर्णांक;


/*
 * SVGA Device Capabilities
 *
 * Note the holes in the bitfield. Missing bits have been deprecated,
 * and must not be reused. Those capabilities will never be reported
 * by new versions of the SVGA device.
 *
 * SVGA_CAP_IRQMASK --
 *    Provides device पूर्णांकerrupts.  Adds device रेजिस्टर SVGA_REG_IRQMASK
 *    to set पूर्णांकerrupt mask and direct I/O port SVGA_IRQSTATUS_PORT to
 *    set/clear pending पूर्णांकerrupts.
 *
 * SVGA_CAP_GMR --
 *    Provides synchronous mapping of guest memory regions (GMR).
 *    Adds device रेजिस्टरs SVGA_REG_GMR_ID, SVGA_REG_GMR_DESCRIPTOR,
 *    SVGA_REG_GMR_MAX_IDS, and SVGA_REG_GMR_MAX_DESCRIPTOR_LENGTH.
 *
 * SVGA_CAP_TRACES --
 *    Allows framebuffer trace-based updates even when FIFO is enabled.
 *    Adds device रेजिस्टर SVGA_REG_TRACES.
 *
 * SVGA_CAP_GMR2 --
 *    Provides asynchronous commands to define and remap guest memory
 *    regions.  Adds device रेजिस्टरs SVGA_REG_GMRS_MAX_PAGES and
 *    SVGA_REG_MEMORY_SIZE.
 *
 * SVGA_CAP_SCREEN_OBJECT_2 --
 *    Allow screen object support, and require backing stores from the
 *    guest क्रम each screen object.
 *
 * SVGA_CAP_COMMAND_BUFFERS --
 *    Enable रेजिस्टर based command buffer submission.
 *
 * SVGA_CAP_DEAD1 --
 *    This cap was incorrectly used by old drivers and should not be
 *    reused.
 *
 * SVGA_CAP_CMD_BUFFERS_2 --
 *    Enable support क्रम the prepend command buffer submision
 *    रेजिस्टरs.  SVGA_REG_CMD_PREPEND_LOW and
 *    SVGA_REG_CMD_PREPEND_HIGH.
 *
 * SVGA_CAP_GBOBJECTS --
 *    Enable guest-backed objects and surfaces.
 *
 * SVGA_CAP_DX --
 *    Enable support क्रम DX commands, and command buffers in a mob.
 *
 * SVGA_CAP_HP_CMD_QUEUE --
 *    Enable support क्रम the high priority command queue, and the
 *    ScreenCopy command.
 *
 * SVGA_CAP_NO_BB_RESTRICTION --
 *    Allow ScreenTarमाला_लो to be defined without regard to the 32-bpp
 *    bounding-box memory restrictions. ie:
 *
 *    The summed memory usage of all screens (assuming they were defined as
 *    32-bpp) must always be less than the value of the
 *    SVGA_REG_MAX_PRIMARY_MEM रेजिस्टर.
 *
 *    If this cap is not present, the 32-bpp bounding box around all screens
 *    must additionally be under the value of the SVGA_REG_MAX_PRIMARY_MEM
 *    रेजिस्टर.
 *
 *    If the cap is present, the bounding box restriction is lअगरted (and only
 *    the screen-sum limit applies).
 *
 *    (Note that this is a slight lie... there is still a sanity limit on any
 *     dimension of the topology to be less than SVGA_SCREEN_ROOT_LIMIT, even
 *     when SVGA_CAP_NO_BB_RESTRICTION is present, but that should be
 *     large enough to express any possible topology without holes between
 *     monitors.)
 *
 * SVGA_CAP_CAP2_REGISTER --
 *    If this cap is present, the SVGA_REG_CAP2 रेजिस्टर is supported.
 */

#घोषणा SVGA_CAP_NONE               0x00000000
#घोषणा SVGA_CAP_RECT_COPY          0x00000002
#घोषणा SVGA_CAP_CURSOR             0x00000020
#घोषणा SVGA_CAP_CURSOR_BYPASS      0x00000040
#घोषणा SVGA_CAP_CURSOR_BYPASS_2    0x00000080
#घोषणा SVGA_CAP_8BIT_EMULATION     0x00000100
#घोषणा SVGA_CAP_ALPHA_CURSOR       0x00000200
#घोषणा SVGA_CAP_3D                 0x00004000
#घोषणा SVGA_CAP_EXTENDED_FIFO      0x00008000
#घोषणा SVGA_CAP_MULTIMON           0x00010000
#घोषणा SVGA_CAP_PITCHLOCK          0x00020000
#घोषणा SVGA_CAP_IRQMASK            0x00040000
#घोषणा SVGA_CAP_DISPLAY_TOPOLOGY   0x00080000
#घोषणा SVGA_CAP_GMR                0x00100000
#घोषणा SVGA_CAP_TRACES             0x00200000
#घोषणा SVGA_CAP_GMR2               0x00400000
#घोषणा SVGA_CAP_SCREEN_OBJECT_2    0x00800000
#घोषणा SVGA_CAP_COMMAND_BUFFERS    0x01000000
#घोषणा SVGA_CAP_DEAD1              0x02000000
#घोषणा SVGA_CAP_CMD_BUFFERS_2      0x04000000
#घोषणा SVGA_CAP_GBOBJECTS          0x08000000
#घोषणा SVGA_CAP_DX                 0x10000000
#घोषणा SVGA_CAP_HP_CMD_QUEUE       0x20000000
#घोषणा SVGA_CAP_NO_BB_RESTRICTION  0x40000000
#घोषणा SVGA_CAP_CAP2_REGISTER      0x80000000

/*
 * The SVGA_REG_CAP2 रेजिस्टर is an additional set of SVGA capability bits.
 *
 * SVGA_CAP2_GROW_OTABLE --
 *      Allow the GrowOTable/DXGrowCOTable commands.
 *
 * SVGA_CAP2_INTRA_SURFACE_COPY --
 *      Allow the IntraSurfaceCopy command.
 *
 * SVGA_CAP2_DX2 --
 *      Allow the DefineGBSurface_v3, WholeSurfaceCopy, WriteZeroSurface, and
 *      Hपूर्णांकZeroSurface commands, and the SVGA_REG_GUEST_DRIVER_ID रेजिस्टर.
 *
 * SVGA_CAP2_GB_MEMSIZE_2 --
 *      Allow the SVGA_REG_GBOBJECT_MEM_SIZE_KB रेजिस्टर.
 *
 * SVGA_CAP2_SCREENDMA_REG --
 *      Allow the SVGA_REG_SCREENDMA रेजिस्टर.
 *
 * SVGA_CAP2_OTABLE_PTDEPTH_2 --
 *      Allow 2 level page tables क्रम OTable commands.
 *
 * SVGA_CAP2_NON_MS_TO_MS_STRETCHBLT --
 *      Allow a stretch blt from a non-multisampled surface to a multisampled
 *      surface.
 *
 * SVGA_CAP2_CURSOR_MOB --
 *      Allow the SVGA_REG_CURSOR_MOBID रेजिस्टर.
 *
 * SVGA_CAP2_MSHINT --
 *      Allow the SVGA_REG_MSHINT रेजिस्टर.
 *
 * SVGA_CAP2_DX3 --
 *      Allows the DefineGBSurface_v4 command.
 *      Allows the DXDefineDepthStencilView_v2, DXDefineStreamOutputWithMob,
 *      and DXBindStreamOutput commands अगर 3D is also available.
 *      Allows the DXPredStagingCopy and DXStagingCopy commands अगर SM41
 *      is also available.
 *
 * SVGA_CAP2_RESERVED --
 *      Reserve the last bit क्रम extending the SVGA capabilities to some
 *      future mechanisms.
 */
#घोषणा SVGA_CAP2_NONE                    0x00000000
#घोषणा SVGA_CAP2_GROW_OTABLE             0x00000001
#घोषणा SVGA_CAP2_INTRA_SURFACE_COPY      0x00000002
#घोषणा SVGA_CAP2_DX2                     0x00000004
#घोषणा SVGA_CAP2_GB_MEMSIZE_2            0x00000008
#घोषणा SVGA_CAP2_SCREENDMA_REG           0x00000010
#घोषणा SVGA_CAP2_OTABLE_PTDEPTH_2        0x00000020
#घोषणा SVGA_CAP2_NON_MS_TO_MS_STRETCHBLT 0x00000040
#घोषणा SVGA_CAP2_CURSOR_MOB              0x00000080
#घोषणा SVGA_CAP2_MSHINT                  0x00000100
#घोषणा SVGA_CAP2_DX3                     0x00000400
#घोषणा SVGA_CAP2_RESERVED                0x80000000


/*
 * The Guest can optionally पढ़ो some SVGA device capabilities through
 * the backकरोor with command BDOOR_CMD_GET_SVGA_CAPABILITIES beक्रमe
 * the SVGA device is initialized.  The type of capability the guest
 * is requesting from the SVGABackकरोorCapType क्रमागत should be placed in
 * the upper 16 bits of the backकरोor command id (ECX).  On success the
 * the value of EBX will be set to BDOOR_MAGIC and EAX will be set to
 * the requested capability.  If the command is not supported then EBX
 * will be left unchanged and EAX will be set to -1.  Because it is
 * possible that -1 is the value of the requested cap the correct way
 * to check अगर the command was successful is to check अगर EBX was changed
 * to BDOOR_MAGIC making sure to initialize the रेजिस्टर to something
 * अन्यथा first.
 */

प्रकार क्रमागत अणु
   SVGABackकरोorCapDeviceCaps = 0,
   SVGABackकरोorCapFअगरoCaps = 1,
   SVGABackकरोorCap3dHWVersion = 2,
   SVGABackकरोorCapDeviceCaps2 = 3,
   SVGABackकरोorCapDevelCaps = 4,
   SVGABackकरोorDevelRenderer = 5,
   SVGABackकरोorCapMax = 6,
पूर्ण SVGABackकरोorCapType;


/*
 * FIFO रेजिस्टर indices.
 *
 * The FIFO is a chunk of device memory mapped पूर्णांकo guest physmem.  It
 * is always treated as 32-bit words.
 *
 * The guest driver माला_लो to decide how to partition it between
 * - FIFO रेजिस्टरs (there are always at least 4, specअगरying where the
 *   following data area is and how much data it contains; there may be
 *   more रेजिस्टरs following these, depending on the FIFO protocol
 *   version in use)
 * - FIFO data, written by the guest and slurped out by the VMX.
 * These indices are 32-bit word offsets पूर्णांकo the FIFO.
 */

क्रमागत अणु
   /*
    * Block 1 (basic रेजिस्टरs): The originally defined FIFO रेजिस्टरs.
    * These exist and are valid क्रम all versions of the FIFO protocol.
    */

   SVGA_FIFO_MIN = 0,
   SVGA_FIFO_MAX,       /* The distance from MIN to MAX must be at least 10K */
   SVGA_FIFO_NEXT_CMD,
   SVGA_FIFO_STOP,

   /*
    * Block 2 (extended रेजिस्टरs): Mandatory रेजिस्टरs क्रम the extended
    * FIFO.  These exist अगर the SVGA caps रेजिस्टर includes
    * SVGA_CAP_EXTENDED_FIFO; some of them are valid only अगर their
    * associated capability bit is enabled.
    *
    * Note that when originally defined, SVGA_CAP_EXTENDED_FIFO implied
    * support only क्रम (FIFO रेजिस्टरs) CAPABILITIES, FLAGS, and FENCE.
    * This means that the guest has to test inभागidually (in most हालs
    * using FIFO caps) क्रम the presence of रेजिस्टरs after this; the VMX
    * can define "extended FIFO" to mean whatever it wants, and currently
    * won't enable it unless there's room क्रम that set and much more.
    */

   SVGA_FIFO_CAPABILITIES = 4,
   SVGA_FIFO_FLAGS,
   /* Valid with SVGA_FIFO_CAP_FENCE: */
   SVGA_FIFO_FENCE,

   /*
    * Block 3a (optional extended रेजिस्टरs): Additional रेजिस्टरs क्रम the
    * extended FIFO, whose presence isn't actually implied by
    * SVGA_CAP_EXTENDED_FIFO; these exist अगर SVGA_FIFO_MIN is high enough to
    * leave room क्रम them.
    *
    * These in block 3a, the VMX currently considers mandatory क्रम the
    * extended FIFO.
    */

   /* Valid अगर exists (i.e. अगर extended FIFO enabled): */
   SVGA_FIFO_3D_HWVERSION,       /* See SVGA3dHardwareVersion in svga3d_reg.h */
   /* Valid with SVGA_FIFO_CAP_PITCHLOCK: */
   SVGA_FIFO_PITCHLOCK,

   /* Valid with SVGA_FIFO_CAP_CURSOR_BYPASS_3: */
   SVGA_FIFO_CURSOR_ON,          /* Cursor bypass 3 show/hide रेजिस्टर */
   SVGA_FIFO_CURSOR_X,           /* Cursor bypass 3 x रेजिस्टर */
   SVGA_FIFO_CURSOR_Y,           /* Cursor bypass 3 y रेजिस्टर */
   SVGA_FIFO_CURSOR_COUNT,       /* Incremented when any of the other 3 change */
   SVGA_FIFO_CURSOR_LAST_UPDATED,/* Last समय the host updated the cursor */

   /* Valid with SVGA_FIFO_CAP_RESERVE: */
   SVGA_FIFO_RESERVED,           /* Bytes past NEXT_CMD with real contents */

   /*
    * Valid with SVGA_FIFO_CAP_SCREEN_OBJECT or SVGA_FIFO_CAP_SCREEN_OBJECT_2:
    *
    * By शेष this is SVGA_ID_INVALID, to indicate that the cursor
    * coordinates are specअगरied relative to the भव root. If this
    * is set to a specअगरic screen ID, cursor position is reपूर्णांकerpreted
    * as a चिन्हित offset relative to that screen's origin.
    */
   SVGA_FIFO_CURSOR_SCREEN_ID,

   /*
    * Valid with SVGA_FIFO_CAP_DEAD
    *
    * An arbitrary value written by the host, drivers should not use it.
    */
   SVGA_FIFO_DEAD,

   /*
    * Valid with SVGA_FIFO_CAP_3D_HWVERSION_REVISED:
    *
    * Contains 3D HWVERSION (see SVGA3dHardwareVersion in svga3d_reg.h)
    * on platक्रमms that can enक्रमce graphics resource limits.
    */
   SVGA_FIFO_3D_HWVERSION_REVISED,

   /*
    * XXX: The gap here, up until SVGA_FIFO_3D_CAPS, can be used क्रम new
    * रेजिस्टरs, but this must be करोne carefully and with judicious use of
    * capability bits, since comparisons based on SVGA_FIFO_MIN aren't
    * enough to tell you whether the रेजिस्टर exists: we've shipped drivers
    * and products that used SVGA_FIFO_3D_CAPS but didn't know about some of
    * the earlier ones.  The actual order of पूर्णांकroduction was:
    * - PITCHLOCK
    * - 3D_CAPS
    * - CURSOR_* (cursor bypass 3)
    * - RESERVED
    * So, code that wants to know whether it can use any of the
    * aक्रमementioned रेजिस्टरs, or anything अन्यथा added after PITCHLOCK and
    * beक्रमe 3D_CAPS, needs to reason about something other than
    * SVGA_FIFO_MIN.
    */

   /*
    * 3D caps block space; valid with 3D hardware version >=
    * SVGA3D_HWVERSION_WS6_B1.
    */
   SVGA_FIFO_3D_CAPS      = 32,
   SVGA_FIFO_3D_CAPS_LAST = 32 + 255,

   /*
    * End of VMX's current definition of "extended-FIFO registers".
    * Registers beक्रमe here are always enabled/disabled as a block; either
    * the extended FIFO is enabled and includes all preceding रेजिस्टरs, or
    * it's disabled entirely.
    *
    * Block 3b (truly optional extended रेजिस्टरs): Additional रेजिस्टरs क्रम
    * the extended FIFO, which the VMX alपढ़ोy knows how to enable and
    * disable with correct granularity.
    *
    * Registers after here exist अगर and only अगर the guest SVGA driver
    * sets SVGA_FIFO_MIN high enough to leave room क्रम them.
    */

   /* Valid अगर रेजिस्टर exists: */
   SVGA_FIFO_GUEST_3D_HWVERSION, /* Guest driver's 3D version */
   SVGA_FIFO_FENCE_GOAL,         /* Matching target क्रम SVGA_IRQFLAG_FENCE_GOAL */
   SVGA_FIFO_BUSY,               /* See "FIFO Synchronization Registers" */

   /*
    * Always keep this last.  This defines the maximum number of
    * रेजिस्टरs we know about.  At घातer-on, this value is placed in
    * the SVGA_REG_MEM_REGS रेजिस्टर, and we expect the guest driver
    * to allocate this much space in FIFO memory क्रम रेजिस्टरs.
    */
    SVGA_FIFO_NUM_REGS
पूर्ण;


/*
 * Definition of रेजिस्टरs included in extended FIFO support.
 *
 * The guest SVGA driver माला_लो to allocate the FIFO between रेजिस्टरs
 * and data.  It must always allocate at least 4 रेजिस्टरs, but old
 * drivers stopped there.
 *
 * The VMX will enable extended FIFO support अगर and only अगर the guest
 * left enough room क्रम all रेजिस्टरs defined as part of the mandatory
 * set क्रम the extended FIFO.
 *
 * Note that the guest drivers typically allocate the FIFO only at
 * initialization समय, not at mode चयनes, so it's likely that the
 * number of FIFO रेजिस्टरs won't change without a reboot.
 *
 * All रेजिस्टरs less than this value are guaranteed to be present अगर
 * svgaUser->fअगरo.extended is set. Any later रेजिस्टरs must be tested
 * inभागidually क्रम compatibility at each use (in the VMX).
 *
 * This value is used only by the VMX, so it can change without
 * affecting driver compatibility; keep it that way?
 */
#घोषणा SVGA_FIFO_EXTENDED_MANDATORY_REGS  (SVGA_FIFO_3D_CAPS_LAST + 1)


/*
 * FIFO Synchronization Registers
 *
 *  SVGA_REG_SYNC --
 *
 *       The SYNC रेजिस्टर can be used by the guest driver to संकेत to the
 *       device that the guest driver is रुकोing क्रम previously submitted
 *       commands to complete.
 *
 *       When the guest driver ग_लिखोs to the SYNC रेजिस्टर, the device sets
 *       the BUSY रेजिस्टर to TRUE, and starts processing the submitted commands
 *       (अगर it was not alपढ़ोy करोing so).  When all previously submitted
 *       commands are finished and the device is idle again, it sets the BUSY
 *       रेजिस्टर back to FALSE.  (If the guest driver submits new commands
 *       after writing the SYNC रेजिस्टर, the new commands are not guaranteed
 *       to have been procesesd.)
 *
 *       When guest drivers are submitting commands using the FIFO, the device
 *       periodically polls to check क्रम new FIFO commands when idle, which may
 *       पूर्णांकroduce a delay in command processing.  If the guest-driver wants
 *       the commands to be processed quickly (which it typically करोes), it
 *       should ग_लिखो SYNC after each batch of commands is committed to the
 *       FIFO to immediately wake up the device.  For even better perक्रमmance,
 *       the guest can use the SVGA_FIFO_BUSY रेजिस्टर to aव्योम these extra
 *       SYNC ग_लिखोs अगर the device is alपढ़ोy active, using the technique known
 *       as "Ringing the Doorbell" (described below).  (Note that command
 *       buffer submission implicitly wakes up the device, and so करोesn't
 *       suffer from this problem.)
 *
 *       The SYNC रेजिस्टर can also be used in combination with BUSY to
 *       synchronously ensure that all SVGA commands are processed (with both
 *       the FIFO and command-buffers).  To करो this, the guest driver should
 *       ग_लिखो to SYNC, and then loop पढ़ोing BUSY until BUSY वापसs FALSE.
 *       This technique is known as a "Legacy Sync".
 *
 *  SVGA_REG_BUSY --
 *
 *       This रेजिस्टर is set to TRUE when SVGA_REG_SYNC is written,
 *       and is set back to FALSE when the device has finished processing
 *       all commands and is idle again.
 *
 *       Every पढ़ो from the BUSY reigster will block क्रम an undefined
 *       amount of समय (normally until the device finishes some पूर्णांकeresting
 *       work unit), or the device is idle.
 *
 *       Guest drivers can also करो a partial Legacy Sync to check क्रम some
 *       particular condition, क्रम instance by stopping early when a fence
 *       passes beक्रमe BUSY has been set back to FALSE.  This is particularly
 *       useful अगर the guest-driver knows that it is blocked रुकोing on the
 *       device, because it will yield CPU समय back to the host.
 *
 *  SVGA_FIFO_BUSY --
 *
 *       The SVGA_FIFO_BUSY रेजिस्टर is a fast way क्रम the guest driver to check
 *       whether the device is actively processing FIFO commands beक्रमe writing
 *       the more expensive SYNC रेजिस्टर.
 *
 *       If this रेजिस्टर पढ़ोs as TRUE, the device is actively processing
 *       FIFO commands.
 *
 *       If this रेजिस्टर पढ़ोs as FALSE, the device may not be actively
 *       processing commands, and the guest driver should try
 *       "Ringing the Doorbell".
 *
 *       To Ring the Doorbell, the guest should:
 *
 *       1. Have alपढ़ोy written their batch of commands पूर्णांकo the FIFO.
 *       2. Check अगर the SVGA_FIFO_BUSY रेजिस्टर is available by पढ़ोing
 *          SVGA_FIFO_MIN.
 *       3. Read SVGA_FIFO_BUSY.  If it पढ़ोs as TRUE, the device is actively
 *          processing FIFO commands, and no further action is necessary.
 *       4. If SVGA_FIFO_BUSY was FALSE, ग_लिखो TRUE to SVGA_REG_SYNC.
 *
 *       For maximum perक्रमmance, this procedure should be followed after
 *       every meaningful batch of commands has been written पूर्णांकo the FIFO.
 *       (Normally when the underlying application संकेतs it's finished a
 *       meaningful work unit by calling Flush.)
 */


/*
 * FIFO Capabilities
 *
 *      Fence -- Fence रेजिस्टर and command are supported
 *      Accel Front -- Front buffer only commands are supported
 *      Pitch Lock -- Pitch lock रेजिस्टर is supported
 *      Video -- SVGA Video overlay units are supported
 *      Escape -- Escape command is supported
 *
 * SVGA_FIFO_CAP_SCREEN_OBJECT --
 *
 *    Provides dynamic multi-screen rendering, क्रम improved Unity and
 *    multi-monitor modes. With Screen Object, the guest can
 *    dynamically create and destroy 'screens', which can represent
 *    Unity winकरोws or भव monitors. Screen Object also provides
 *    strong guarantees that DMA operations happen only when
 *    guest-initiated. Screen Object deprecates the BAR1 guest
 *    framebuffer (GFB) and all commands that work only with the GFB.
 *
 *    New रेजिस्टरs:
 *       FIFO_CURSOR_SCREEN_ID, VIDEO_DATA_GMRID, VIDEO_DST_SCREEN_ID
 *
 *    New 2D commands:
 *       DEFINE_SCREEN, DESTROY_SCREEN, DEFINE_GMRFB, BLIT_GMRFB_TO_SCREEN,
 *       BLIT_SCREEN_TO_GMRFB, ANNOTATION_FILL, ANNOTATION_COPY
 *
 *    New 3D commands:
 *       BLIT_SURFACE_TO_SCREEN
 *
 *    New guarantees:
 *
 *       - The host will not पढ़ो or ग_लिखो guest memory, including the GFB,
 *         except when explicitly initiated by a DMA command.
 *
 *       - All DMA, including legacy DMA like UPDATE and PRESENT_READBACK,
 *         is guaranteed to complete beक्रमe any subsequent FENCEs.
 *
 *       - All legacy commands which affect a Screen (UPDATE, PRESENT,
 *         PRESENT_READBACK) as well as new Screen blit commands will
 *         all behave consistently as blits, and memory will be पढ़ो
 *         or written in FIFO order.
 *
 *         For example, अगर you PRESENT from one SVGA3D surface to multiple
 *         places on the screen, the data copied will always be from the
 *         SVGA3D surface at the समय the PRESENT was issued in the FIFO.
 *         This was not necessarily true on devices without Screen Object.
 *
 *         This means that on devices that support Screen Object, the
 *         PRESENT_READBACK command should not be necessary unless you
 *         actually want to पढ़ो back the results of 3D rendering पूर्णांकo
 *         प्रणाली memory. (And क्रम that, the BLIT_SCREEN_TO_GMRFB
 *         command provides a strict superset of functionality.)
 *
 *       - When a screen is resized, either using Screen Object commands or
 *         legacy multimon रेजिस्टरs, its contents are preserved.
 *
 * SVGA_FIFO_CAP_GMR2 --
 *
 *    Provides new commands to define and remap guest memory regions (GMR).
 *
 *    New 2D commands:
 *       DEFINE_GMR2, REMAP_GMR2.
 *
 * SVGA_FIFO_CAP_3D_HWVERSION_REVISED --
 *
 *    Indicates new रेजिस्टर SVGA_FIFO_3D_HWVERSION_REVISED exists.
 *    This रेजिस्टर may replace SVGA_FIFO_3D_HWVERSION on platक्रमms
 *    that enक्रमce graphics resource limits.  This allows the platक्रमm
 *    to clear SVGA_FIFO_3D_HWVERSION and disable 3D in legacy guest
 *    drivers that करो not limit their resources.
 *
 *    Note this is an alias to SVGA_FIFO_CAP_GMR2 because these indicators
 *    are codependent (and thus we use a single capability bit).
 *
 * SVGA_FIFO_CAP_SCREEN_OBJECT_2 --
 *
 *    Modअगरies the DEFINE_SCREEN command to include a guest provided
 *    backing store in GMR memory and the bytesPerLine क्रम the backing
 *    store.  This capability requires the use of a backing store when
 *    creating screen objects.  However अगर SVGA_FIFO_CAP_SCREEN_OBJECT
 *    is present then backing stores are optional.
 *
 * SVGA_FIFO_CAP_DEAD --
 *
 *    Drivers should not use this cap bit.  This cap bit can not be
 *    reused since some hosts alपढ़ोy expose it.
 */

#घोषणा SVGA_FIFO_CAP_NONE                  0
#घोषणा SVGA_FIFO_CAP_FENCE             (1<<0)
#घोषणा SVGA_FIFO_CAP_ACCELFRONT        (1<<1)
#घोषणा SVGA_FIFO_CAP_PITCHLOCK         (1<<2)
#घोषणा SVGA_FIFO_CAP_VIDEO             (1<<3)
#घोषणा SVGA_FIFO_CAP_CURSOR_BYPASS_3   (1<<4)
#घोषणा SVGA_FIFO_CAP_ESCAPE            (1<<5)
#घोषणा SVGA_FIFO_CAP_RESERVE           (1<<6)
#घोषणा SVGA_FIFO_CAP_SCREEN_OBJECT     (1<<7)
#घोषणा SVGA_FIFO_CAP_GMR2              (1<<8)
#घोषणा SVGA_FIFO_CAP_3D_HWVERSION_REVISED  SVGA_FIFO_CAP_GMR2
#घोषणा SVGA_FIFO_CAP_SCREEN_OBJECT_2   (1<<9)
#घोषणा SVGA_FIFO_CAP_DEAD              (1<<10)


/*
 * FIFO Flags
 *
 *      Accel Front -- Driver should use front buffer only commands
 */

#घोषणा SVGA_FIFO_FLAG_NONE                 0
#घोषणा SVGA_FIFO_FLAG_ACCELFRONT       (1<<0)
#घोषणा SVGA_FIFO_FLAG_RESERVED        (1<<31) /* Internal use only */

/*
 * FIFO reservation sentinel value
 */

#घोषणा SVGA_FIFO_RESERVED_UNKNOWN      0xffffffff


/*
 * ScreenDMA Register Values
 */

#घोषणा SVGA_SCREENDMA_REG_UNDEFINED    0
#घोषणा SVGA_SCREENDMA_REG_NOT_PRESENT  1
#घोषणा SVGA_SCREENDMA_REG_PRESENT      2
#घोषणा SVGA_SCREENDMA_REG_MAX          3

/*
 * Video overlay support
 */

#घोषणा SVGA_NUM_OVERLAY_UNITS 32


/*
 * Video capabilities that the guest is currently using
 */

#घोषणा SVGA_VIDEO_FLAG_COLORKEY        0x0001


/*
 * Offsets क्रम the video overlay रेजिस्टरs
 */

क्रमागत अणु
   SVGA_VIDEO_ENABLED = 0,
   SVGA_VIDEO_FLAGS,
   SVGA_VIDEO_DATA_OFFSET,
   SVGA_VIDEO_FORMAT,
   SVGA_VIDEO_COLORKEY,
   SVGA_VIDEO_SIZE,          /* Deprecated */
   SVGA_VIDEO_WIDTH,
   SVGA_VIDEO_HEIGHT,
   SVGA_VIDEO_SRC_X,
   SVGA_VIDEO_SRC_Y,
   SVGA_VIDEO_SRC_WIDTH,
   SVGA_VIDEO_SRC_HEIGHT,
   SVGA_VIDEO_DST_X,         /* Signed पूर्णांक32 */
   SVGA_VIDEO_DST_Y,         /* Signed पूर्णांक32 */
   SVGA_VIDEO_DST_WIDTH,
   SVGA_VIDEO_DST_HEIGHT,
   SVGA_VIDEO_PITCH_1,
   SVGA_VIDEO_PITCH_2,
   SVGA_VIDEO_PITCH_3,
   SVGA_VIDEO_DATA_GMRID,    /* Optional, शेषs to SVGA_GMR_FRAMEBUFFER */
   SVGA_VIDEO_DST_SCREEN_ID, /* Optional, शेषs to भव coords */
                             /* (SVGA_ID_INVALID) */
   SVGA_VIDEO_NUM_REGS
पूर्ण;


/*
 * SVGA Overlay Units
 *
 *      width and height relate to the entire source video frame.
 *      srcX, srcY, srcWidth and srcHeight represent subset of the source
 *      video frame to be displayed.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGAOverlayUnit अणु
   uपूर्णांक32 enabled;
   uपूर्णांक32 flags;
   uपूर्णांक32 dataOffset;
   uपूर्णांक32 क्रमmat;
   uपूर्णांक32 colorKey;
   uपूर्णांक32 size;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   uपूर्णांक32 srcX;
   uपूर्णांक32 srcY;
   uपूर्णांक32 srcWidth;
   uपूर्णांक32 srcHeight;
   पूर्णांक32  dstX;
   पूर्णांक32  dstY;
   uपूर्णांक32 dstWidth;
   uपूर्णांक32 dstHeight;
   uपूर्णांक32 pitches[3];
   uपूर्णांक32 dataGMRId;
   uपूर्णांक32 dstScreenId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAOverlayUnit;


/*
 * Guest display topology
 *
 * XXX: This काष्ठाure is not part of the SVGA device's पूर्णांकerface, and
 * करोesn't really beदीर्घ here.
 */
#घोषणा SVGA_INVALID_DISPLAY_ID ((uपूर्णांक32)-1)

प्रकार काष्ठा SVGADisplayTopology अणु
   uपूर्णांक16 displayId;
   uपूर्णांक16 isPrimary;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   uपूर्णांक32 positionX;
   uपूर्णांक32 positionY;
पूर्ण SVGADisplayTopology;


/*
 * SVGAScreenObject --
 *
 *    This is a new way to represent a guest's multi-monitor screen or
 *    Unity winकरोw. Screen objects are only supported अगर the
 *    SVGA_FIFO_CAP_SCREEN_OBJECT capability bit is set.
 *
 *    If Screen Objects are supported, they can be used to fully
 *    replace the functionality provided by the framebuffer रेजिस्टरs
 *    (SVGA_REG_WIDTH, HEIGHT, etc.) and by SVGA_CAP_DISPLAY_TOPOLOGY.
 *
 *    The screen object is a काष्ठा with guaranteed binary
 *    compatibility. New flags can be added, and the काष्ठा may grow,
 *    but existing fields must retain their meaning.
 *
 *    Added with SVGA_FIFO_CAP_SCREEN_OBJECT_2 are required fields of
 *    a SVGAGuestPtr that is used to back the screen contents.  This
 *    memory must come from the GFB.  The guest is not allowed to
 *    access the memory and करोing so will have undefined results.  The
 *    backing store is required to be page aligned and the size is
 *    padded to the next page boundry.  The number of pages is:
 *       (bytesPerLine * size.width * 4 + PAGE_SIZE - 1) / PAGE_SIZE
 *
 *    The pitch in the backingStore is required to be at least large
 *    enough to hold a 32bbp scanline.  It is recommended that the
 *    driver pad bytesPerLine क्रम a potential perक्रमmance win.
 *
 *    The cloneCount field is treated as a hपूर्णांक from the guest that
 *    the user wants this display to be cloned, countCount बार.  A
 *    value of zero means no cloning should happen.
 */

#घोषणा SVGA_SCREEN_MUST_BE_SET     (1 << 0)
#घोषणा SVGA_SCREEN_HAS_ROOT SVGA_SCREEN_MUST_BE_SET /* Deprecated */
#घोषणा SVGA_SCREEN_IS_PRIMARY      (1 << 1)
#घोषणा SVGA_SCREEN_FULLSCREEN_HINT (1 << 2)

/*
 * Added with SVGA_FIFO_CAP_SCREEN_OBJECT_2.  When the screen is
 * deactivated the base layer is defined to lose all contents and
 * become black.  When a screen is deactivated the backing store is
 * optional.  When set backingPtr and bytesPerLine will be ignored.
 */
#घोषणा SVGA_SCREEN_DEACTIVATE  (1 << 3)

/*
 * Added with SVGA_FIFO_CAP_SCREEN_OBJECT_2.  When this flag is set
 * the screen contents will be outputted as all black to the user
 * though the base layer contents is preserved.  The screen base layer
 * can still be पढ़ो and written to like normal though the no visible
 * effect will be seen by the user.  When the flag is changed the
 * screen will be blanked or redrawn to the current contents as needed
 * without any extra commands from the driver.  This flag only has an
 * effect when the screen is not deactivated.
 */
#घोषणा SVGA_SCREEN_BLANKING (1 << 4)

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 काष्ठाSize;   /* माप(SVGAScreenObject) */
   uपूर्णांक32 id;
   uपूर्णांक32 flags;
   काष्ठा अणु
      uपूर्णांक32 width;
      uपूर्णांक32 height;
   पूर्ण size;
   काष्ठा अणु
      पूर्णांक32 x;
      पूर्णांक32 y;
   पूर्ण root;

   /*
    * Added and required by SVGA_FIFO_CAP_SCREEN_OBJECT_2, optional
    * with SVGA_FIFO_CAP_SCREEN_OBJECT.
    */
   SVGAGuestImage backingStore;

   /*
    * The cloneCount field is treated as a hपूर्णांक from the guest that
    * the user wants this display to be cloned, cloneCount बार.
    *
    * A value of zero means no cloning should happen.
    */
   uपूर्णांक32 cloneCount;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAScreenObject;


/*
 *  Commands in the command FIFO:
 *
 *  Command IDs defined below are used क्रम the traditional 2D FIFO
 *  communication (not all commands are available क्रम all versions of the
 *  SVGA FIFO protocol).
 *
 *  Note the holes in the command ID numbers: These commands have been
 *  deprecated, and the old IDs must not be reused.
 *
 *  Command IDs from 1000 to 2999 are reserved क्रम use by the SVGA3D
 *  protocol.
 *
 *  Each command's parameters are described by the comments and
 *  काष्ठाs below.
 */

प्रकार क्रमागत अणु
   SVGA_CMD_INVALID_CMD           = 0,
   SVGA_CMD_UPDATE                = 1,
   SVGA_CMD_RECT_COPY             = 3,
   SVGA_CMD_RECT_ROP_COPY         = 14,
   SVGA_CMD_DEFINE_CURSOR         = 19,
   SVGA_CMD_DEFINE_ALPHA_CURSOR   = 22,
   SVGA_CMD_UPDATE_VERBOSE        = 25,
   SVGA_CMD_FRONT_ROP_FILL        = 29,
   SVGA_CMD_FENCE                 = 30,
   SVGA_CMD_ESCAPE                = 33,
   SVGA_CMD_DEFINE_SCREEN         = 34,
   SVGA_CMD_DESTROY_SCREEN        = 35,
   SVGA_CMD_DEFINE_GMRFB          = 36,
   SVGA_CMD_BLIT_GMRFB_TO_SCREEN  = 37,
   SVGA_CMD_BLIT_SCREEN_TO_GMRFB  = 38,
   SVGA_CMD_ANNOTATION_FILL       = 39,
   SVGA_CMD_ANNOTATION_COPY       = 40,
   SVGA_CMD_DEFINE_GMR2           = 41,
   SVGA_CMD_REMAP_GMR2            = 42,
   SVGA_CMD_DEAD                  = 43,
   SVGA_CMD_DEAD_2                = 44,
   SVGA_CMD_NOP                   = 45,
   SVGA_CMD_NOP_ERROR             = 46,
   SVGA_CMD_MAX
पूर्ण SVGAFअगरoCmdId;

#घोषणा SVGA_CMD_MAX_DATASIZE       (256 * 1024)
#घोषणा SVGA_CMD_MAX_ARGS           64


/*
 * SVGA_CMD_UPDATE --
 *
 *    This is a DMA transfer which copies from the Guest Framebuffer
 *    (GFB) at BAR1 + SVGA_REG_FB_OFFSET to any screens which
 *    पूर्णांकersect with the provided भव rectangle.
 *
 *    This command करोes not support using arbitrary guest memory as a
 *    data source- it only works with the pre-defined GFB memory.
 *    This command also करोes not support चिन्हित भव coordinates.
 *    If you have defined screens (using SVGA_CMD_DEFINE_SCREEN) with
 *    negative root x/y coordinates, the negative portion of those
 *    screens will not be reachable by this command.
 *
 *    This command is not necessary when using framebuffer
 *    traces. Traces are स्वतःmatically enabled अगर the SVGA FIFO is
 *    disabled, and you may explicitly enable/disable traces using
 *    SVGA_REG_TRACES. With traces enabled, any ग_लिखो to the GFB will
 *    स्वतःmatically act as अगर a subsequent SVGA_CMD_UPDATE was issued.
 *
 *    Traces and SVGA_CMD_UPDATE are the only supported ways to render
 *    pseuकरोcolor screen updates. The newer Screen Object commands
 *    only support true color क्रमmats.
 *
 * Availability:
 *    Always available.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 x;
   uपूर्णांक32 y;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdUpdate;


/*
 * SVGA_CMD_RECT_COPY --
 *
 *    Perक्रमm a rectangular DMA transfer from one area of the GFB to
 *    another, and copy the result to any screens which पूर्णांकersect it.
 *
 * Availability:
 *    SVGA_CAP_RECT_COPY
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 srcX;
   uपूर्णांक32 srcY;
   uपूर्णांक32 destX;
   uपूर्णांक32 destY;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdRectCopy;


/*
 * SVGA_CMD_RECT_ROP_COPY --
 *
 *    Perक्रमm a rectangular DMA transfer from one area of the GFB to
 *    another, and copy the result to any screens which पूर्णांकersect it.
 *    The value of ROP may only be SVGA_ROP_COPY, and this command is
 *    only supported क्रम backwards compatibility reasons.
 *
 * Availability:
 *    SVGA_CAP_RECT_COPY
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 srcX;
   uपूर्णांक32 srcY;
   uपूर्णांक32 destX;
   uपूर्णांक32 destY;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   uपूर्णांक32 rop;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdRectRopCopy;


/*
 * SVGA_CMD_DEFINE_CURSOR --
 *
 *    Provide a new cursor image, as an AND/XOR mask.
 *
 *    The recommended way to position the cursor overlay is by using
 *    the SVGA_FIFO_CURSOR_* रेजिस्टरs, supported by the
 *    SVGA_FIFO_CAP_CURSOR_BYPASS_3 capability.
 *
 * Availability:
 *    SVGA_CAP_CURSOR
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 id;             /* Reserved, must be zero. */
   uपूर्णांक32 hotspotX;
   uपूर्णांक32 hotspotY;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   uपूर्णांक32 andMaskDepth;   /* Value must be 1 or equal to BITS_PER_PIXEL */
   uपूर्णांक32 xorMaskDepth;   /* Value must be 1 or equal to BITS_PER_PIXEL */
   /*
    * Followed by scanline data क्रम AND mask, then XOR mask.
    * Each scanline is padded to a 32-bit boundary.
   */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdDefineCursor;


/*
 * SVGA_CMD_DEFINE_ALPHA_CURSOR --
 *
 *    Provide a new cursor image, in 32-bit BGRA क्रमmat.
 *
 *    The recommended way to position the cursor overlay is by using
 *    the SVGA_FIFO_CURSOR_* रेजिस्टरs, supported by the
 *    SVGA_FIFO_CAP_CURSOR_BYPASS_3 capability.
 *
 * Availability:
 *    SVGA_CAP_ALPHA_CURSOR
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 id;             /* Reserved, must be zero. */
   uपूर्णांक32 hotspotX;
   uपूर्णांक32 hotspotY;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   /* Followed by scanline data */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdDefineAlphaCursor;


/*
 *    Provide a new large cursor image, as an AND/XOR mask.
 *
 *    Should only be used क्रम CursorMob functionality
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 hotspotX;
   uपूर्णांक32 hotspotY;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   uपूर्णांक32 andMaskDepth;
   uपूर्णांक32 xorMaskDepth;
   /*
    * Followed by scanline data क्रम AND mask, then XOR mask.
    * Each scanline is padded to a 32-bit boundary.
   */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAGBColorCursorHeader;


/*
 *    Provide a new large cursor image, in 32-bit BGRA क्रमmat.
 *
 *    Should only be used क्रम CursorMob functionality
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 hotspotX;
   uपूर्णांक32 hotspotY;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   /* Followed by scanline data */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAGBAlphaCursorHeader;

 /*
  * Define the SVGA guest backed cursor types
  */

प्रकार क्रमागत अणु
   SVGA_COLOR_CURSOR       = 0,
   SVGA_ALPHA_CURSOR       = 1,
पूर्ण SVGAGBCursorType;

/*
 *    Provide a new large cursor image.
 *
 *    Should only be used क्रम CursorMob functionality
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAGBCursorType type;
   जोड़ अणु
      SVGAGBColorCursorHeader colorHeader;
      SVGAGBAlphaCursorHeader alphaHeader;
   पूर्ण header;
   uपूर्णांक32 sizeInBytes;
   /*
    * Followed by the cursor data
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAGBCursorHeader;


/*
 * SVGA_CMD_UPDATE_VERBOSE --
 *
 *    Just like SVGA_CMD_UPDATE, but also provide a per-rectangle
 *    'reason' value, an opaque cookie which is used by पूर्णांकernal
 *    debugging tools. Third party drivers should not use this
 *    command.
 *
 * Availability:
 *    SVGA_CAP_EXTENDED_FIFO
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 x;
   uपूर्णांक32 y;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   uपूर्णांक32 reason;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdUpdateVerbose;


/*
 * SVGA_CMD_FRONT_ROP_FILL --
 *
 *    This is a hपूर्णांक which tells the SVGA device that the driver has
 *    just filled a rectangular region of the GFB with a solid
 *    color. Instead of पढ़ोing these pixels from the GFB, the device
 *    can assume that they all equal 'color'. This is primarily used
 *    क्रम remote desktop protocols.
 *
 * Availability:
 *    SVGA_FIFO_CAP_ACCELFRONT
 */

#घोषणा  SVGA_ROP_COPY                    0x03

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 color;     /* In the same क्रमmat as the GFB */
   uपूर्णांक32 x;
   uपूर्णांक32 y;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   uपूर्णांक32 rop;       /* Must be SVGA_ROP_COPY */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdFrontRopFill;


/*
 * SVGA_CMD_FENCE --
 *
 *    Insert a synchronization fence.  When the SVGA device reaches
 *    this command, it will copy the 'fence' value पूर्णांकo the
 *    SVGA_FIFO_FENCE रेजिस्टर. It will also compare the fence against
 *    SVGA_FIFO_FENCE_GOAL. If the fence matches the goal and the
 *    SVGA_IRQFLAG_FENCE_GOAL पूर्णांकerrupt is enabled, the device will
 *    उठाओ this पूर्णांकerrupt.
 *
 * Availability:
 *    SVGA_FIFO_FENCE क्रम this command,
 *    SVGA_CAP_IRQMASK क्रम SVGA_FIFO_FENCE_GOAL.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 fence;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdFence;


/*
 * SVGA_CMD_ESCAPE --
 *
 *    Send an extended or venकरोr-specअगरic variable length command.
 *    This is used क्रम video overlay, third party plugins, and
 *    पूर्णांकernal debugging tools. See svga_escape.h
 *
 * Availability:
 *    SVGA_FIFO_CAP_ESCAPE
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 nsid;
   uपूर्णांक32 size;
   /* followed by 'size' bytes of data */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdEscape;


/*
 * SVGA_CMD_DEFINE_SCREEN --
 *
 *    Define or redefine an SVGAScreenObject. See the description of
 *    SVGAScreenObject above.  The video driver is responsible क्रम
 *    generating new screen IDs. They should be small positive
 *    पूर्णांकegers. The भव device will have an implementation
 *    specअगरic upper limit on the number of screen IDs
 *    supported. Drivers are responsible क्रम recycling IDs. The first
 *    valid ID is zero.
 *
 *    - Interaction with other रेजिस्टरs:
 *
 *    For backwards compatibility, when the GFB mode रेजिस्टरs (WIDTH,
 *    HEIGHT, PITCHLOCK, BITS_PER_PIXEL) are modअगरied, the SVGA device
 *    deletes all screens other than screen #0, and redefines screen
 *    #0 according to the specअगरied mode. Drivers that use
 *    SVGA_CMD_DEFINE_SCREEN should destroy or redefine screen #0.
 *
 *    If you use screen objects, करो not use the legacy multi-mon
 *    रेजिस्टरs (SVGA_REG_NUM_GUEST_DISPLAYS, SVGA_REG_DISPLAY_*).
 *
 * Availability:
 *    SVGA_FIFO_CAP_SCREEN_OBJECT or SVGA_FIFO_CAP_SCREEN_OBJECT_2
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAScreenObject screen;   /* Variable-length according to version */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdDefineScreen;


/*
 * SVGA_CMD_DESTROY_SCREEN --
 *
 *    Destroy an SVGAScreenObject. Its ID is immediately available क्रम
 *    re-use.
 *
 * Availability:
 *    SVGA_FIFO_CAP_SCREEN_OBJECT or SVGA_FIFO_CAP_SCREEN_OBJECT_2
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 screenId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdDestroyScreen;


/*
 * SVGA_CMD_DEFINE_GMRFB --
 *
 *    This command sets a piece of SVGA device state called the
 *    Guest Memory Region Framebuffer, or GMRFB. The GMRFB is a
 *    piece of light-weight state which identअगरies the location and
 *    क्रमmat of an image in guest memory or in BAR1. The GMRFB has
 *    an arbitrary size, and it करोesn't need to match the geometry
 *    of the GFB or any screen object.
 *
 *    The GMRFB can be redefined as often as you like. You could
 *    always use the same GMRFB, you could redefine it beक्रमe
 *    rendering from a dअगरferent guest screen, or you could even
 *    redefine it beक्रमe every blit.
 *
 *    There are multiple ways to use this command. The simplest way is
 *    to use it to move the framebuffer either to अन्यथाwhere in the GFB
 *    (BAR1) memory region, or to a user-defined GMR. This lets a
 *    driver use a framebuffer allocated entirely out of normal प्रणाली
 *    memory, which we encourage.
 *
 *    Another way to use this command is to set up a ring buffer of
 *    updates in GFB memory. If a driver wants to ensure that no
 *    frames are skipped by the SVGA device, it is important that the
 *    driver not modअगरy the source data क्रम a blit until the device is
 *    करोne processing the command. One efficient way to accomplish
 *    this is to use a ring of small DMA buffers. Each buffer is used
 *    क्रम one blit, then we move on to the next buffer in the
 *    ring. The FENCE mechanism is used to protect each buffer from
 *    re-use until the device is finished with that buffer's
 *    corresponding blit.
 *
 *    This command करोes not affect the meaning of SVGA_CMD_UPDATE.
 *    UPDATEs always occur from the legacy GFB memory area. This
 *    command has no support क्रम pseuकरोcolor GMRFBs. Currently only
 *    true-color 15, 16, and 24-bit depths are supported. Future
 *    devices may expose capabilities क्रम additional framebuffer
 *    क्रमmats.
 *
 *    The शेष GMRFB value is undefined. Drivers must always send
 *    this command at least once beक्रमe perक्रमming any blit from the
 *    GMRFB.
 *
 * Availability:
 *    SVGA_FIFO_CAP_SCREEN_OBJECT or SVGA_FIFO_CAP_SCREEN_OBJECT_2
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAGuestPtr        ptr;
   uपूर्णांक32              bytesPerLine;
   SVGAGMRImageFormat  क्रमmat;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdDefineGMRFB;


/*
 * SVGA_CMD_BLIT_GMRFB_TO_SCREEN --
 *
 *    This is a guest-to-host blit. It perक्रमms a DMA operation to
 *    copy a rectangular region of pixels from the current GMRFB to
 *    a ScreenObject.
 *
 *    The destination coordinate may be specअगरied relative to a
 *    screen's origin.  The provided screen ID must be valid.
 *
 *    The SVGA device is guaranteed to finish पढ़ोing from the GMRFB
 *    by the समय any subsequent FENCE commands are reached.
 *
 *    This command consumes an annotation. See the
 *    SVGA_CMD_ANNOTATION_* commands क्रम details.
 *
 * Availability:
 *    SVGA_FIFO_CAP_SCREEN_OBJECT or SVGA_FIFO_CAP_SCREEN_OBJECT_2
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGASignedPoपूर्णांक  srcOrigin;
   SVGASignedRect   destRect;
   uपूर्णांक32           destScreenId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdBlitGMRFBToScreen;


/*
 * SVGA_CMD_BLIT_SCREEN_TO_GMRFB --
 *
 *    This is a host-to-guest blit. It perक्रमms a DMA operation to
 *    copy a rectangular region of pixels from a single ScreenObject
 *    back to the current GMRFB.
 *
 *    The source coordinate is specअगरied relative to a screen's
 *    origin.  The provided screen ID must be valid. If any parameters
 *    are invalid, the resulting pixel values are undefined.
 *
 *    The SVGA device is guaranteed to finish writing to the GMRFB by
 *    the समय any subsequent FENCE commands are reached.
 *
 * Availability:
 *    SVGA_FIFO_CAP_SCREEN_OBJECT or SVGA_FIFO_CAP_SCREEN_OBJECT_2
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGASignedPoपूर्णांक  destOrigin;
   SVGASignedRect   srcRect;
   uपूर्णांक32           srcScreenId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdBlitScreenToGMRFB;


/*
 * SVGA_CMD_ANNOTATION_FILL --
 *
 *    The annotation commands have been deprecated, should not be used
 *    by new drivers.  They used to provide perक्रमmance hपूर्णांकs to the SVGA
 *    device about the content of screen updates, but newer SVGA devices
 *    ignore these.
 *
 * Availability:
 *    SVGA_FIFO_CAP_SCREEN_OBJECT or SVGA_FIFO_CAP_SCREEN_OBJECT_2
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAColorBGRX  color;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdAnnotationFill;


/*
 * SVGA_CMD_ANNOTATION_COPY --
 *
 *    The annotation commands have been deprecated, should not be used
 *    by new drivers.  They used to provide perक्रमmance hपूर्णांकs to the SVGA
 *    device about the content of screen updates, but newer SVGA devices
 *    ignore these.
 *
 * Availability:
 *    SVGA_FIFO_CAP_SCREEN_OBJECT or SVGA_FIFO_CAP_SCREEN_OBJECT_2
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGASignedPoपूर्णांक  srcOrigin;
   uपूर्णांक32           srcScreenId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdAnnotationCopy;


/*
 * SVGA_CMD_DEFINE_GMR2 --
 *
 *    Define guest memory region v2.  See the description of GMRs above.
 *
 * Availability:
 *    SVGA_CAP_GMR2
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 gmrId;
   uपूर्णांक32 numPages;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdDefineGMR2;


/*
 * SVGA_CMD_REMAP_GMR2 --
 *
 *    Remap guest memory region v2.  See the description of GMRs above.
 *
 *    This command allows guest to modअगरy a portion of an existing GMR by
 *    invalidating it or reassigning it to dअगरferent guest physical pages.
 *    The pages are identअगरied by physical page number (PPN).  The pages
 *    are assumed to be pinned and valid क्रम DMA operations.
 *
 *    Description of command flags:
 *
 *    SVGA_REMAP_GMR2_VIA_GMR: If enabled, references a PPN list in a GMR.
 *       The PPN list must not overlap with the remap region (this can be
 *       handled trivially by referencing a separate GMR).  If flag is
 *       disabled, PPN list is appended to SVGARemapGMR command.
 *
 *    SVGA_REMAP_GMR2_PPN64: If set, PPN list is in PPN64 क्रमmat, otherwise
 *       it is in PPN32 क्रमmat.
 *
 *    SVGA_REMAP_GMR2_SINGLE_PPN: If set, PPN list contains a single entry.
 *       A single PPN can be used to invalidate a portion of a GMR or
 *       map it to to a single guest scratch page.
 *
 * Availability:
 *    SVGA_CAP_GMR2
 */

प्रकार क्रमागत अणु
   SVGA_REMAP_GMR2_PPN32         = 0,
   SVGA_REMAP_GMR2_VIA_GMR       = (1 << 0),
   SVGA_REMAP_GMR2_PPN64         = (1 << 1),
   SVGA_REMAP_GMR2_SINGLE_PPN    = (1 << 2),
पूर्ण SVGARemapGMR2Flags;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 gmrId;
   SVGARemapGMR2Flags flags;
   uपूर्णांक32 offsetPages; /* offset in pages to begin remap */
   uपूर्णांक32 numPages; /* number of pages to remap */
   /*
    * Followed by additional data depending on SVGARemapGMR2Flags.
    *
    * If flag SVGA_REMAP_GMR2_VIA_GMR is set, single SVGAGuestPtr follows.
    * Otherwise an array of page descriptors in PPN32 or PPN64 क्रमmat
    * (according to flag SVGA_REMAP_GMR2_PPN64) follows.  If flag
    * SVGA_REMAP_GMR2_SINGLE_PPN is set, array contains a single entry.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAFअगरoCmdRemapGMR2;


/*
 * Size of SVGA device memory such as frame buffer and FIFO.
 */
#घोषणा SVGA_VRAM_MIN_SIZE             (4 * 640 * 480) /* bytes */
#घोषणा SVGA_VRAM_MIN_SIZE_3D       (16 * 1024 * 1024)
#घोषणा SVGA_VRAM_MAX_SIZE         (128 * 1024 * 1024)
#घोषणा SVGA_MEMORY_SIZE_MAX      (1024 * 1024 * 1024)
#घोषणा SVGA_FIFO_SIZE_MAX           (2 * 1024 * 1024)
#घोषणा SVGA_GRAPHICS_MEMORY_KB_MIN     (32 * 1024)
#घोषणा SVGA_GRAPHICS_MEMORY_KB_MAX_2GB (2 * 1024 * 1024)
#घोषणा SVGA_GRAPHICS_MEMORY_KB_MAX_3GB (3 * 1024 * 1024)
#घोषणा SVGA_GRAPHICS_MEMORY_KB_MAX_4GB (4 * 1024 * 1024)
#घोषणा SVGA_GRAPHICS_MEMORY_KB_MAX_8GB (8 * 1024 * 1024)
#घोषणा SVGA_GRAPHICS_MEMORY_KB_DEFAULT (256 * 1024)

#घोषणा SVGA_VRAM_SIZE_W2K          (64 * 1024 * 1024) /* 64 MB */

#अगर defined(VMX86_SERVER)
#घोषणा SVGA_VRAM_SIZE               (4 * 1024 * 1024)
#घोषणा SVGA_VRAM_SIZE_3D           (64 * 1024 * 1024)
#घोषणा SVGA_FIFO_SIZE                    (256 * 1024)
#घोषणा SVGA_FIFO_SIZE_3D                 (516 * 1024)
#घोषणा SVGA_MEMORY_SIZE_DEFAULT   (160 * 1024 * 1024)
#घोषणा SVGA_AUTODETECT_DEFAULT                  FALSE
#अन्यथा
#घोषणा SVGA_VRAM_SIZE              (16 * 1024 * 1024)
#घोषणा SVGA_VRAM_SIZE_3D           SVGA_VRAM_MAX_SIZE
#घोषणा SVGA_FIFO_SIZE               (2 * 1024 * 1024)
#घोषणा SVGA_FIFO_SIZE_3D               SVGA_FIFO_SIZE
#घोषणा SVGA_MEMORY_SIZE_DEFAULT   (768 * 1024 * 1024)
#घोषणा SVGA_AUTODETECT_DEFAULT                   TRUE
#पूर्ण_अगर

#घोषणा SVGA_FIFO_SIZE_GBOBJECTS          (256 * 1024)
#घोषणा SVGA_VRAM_SIZE_GBOBJECTS     (4 * 1024 * 1024)

#घोषणा SVGA_PCI_REGS_PAGES                        (1)

#पूर्ण_अगर
