<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2009 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.
 * Copyright 2009-2010 Jonathan Corbet <corbet@lwn.net>
 * Copyright 2010 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */

#अगर_अघोषित __VIA_CORE_H__
#घोषणा __VIA_CORE_H__
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>

/*
 * A description of each known serial I2C/GPIO port.
 */
क्रमागत via_port_type अणु
	VIA_PORT_NONE = 0,
	VIA_PORT_I2C,
	VIA_PORT_GPIO,
पूर्ण;

क्रमागत via_port_mode अणु
	VIA_MODE_OFF = 0,
	VIA_MODE_I2C,		/* Used as I2C port */
	VIA_MODE_GPIO,	/* Two GPIO ports */
पूर्ण;

क्रमागत viafb_i2c_adap अणु
	VIA_PORT_26 = 0,
	VIA_PORT_31,
	VIA_PORT_25,
	VIA_PORT_2C,
	VIA_PORT_3D,
पूर्ण;
#घोषणा VIAFB_NUM_PORTS 5

काष्ठा via_port_cfg अणु
	क्रमागत via_port_type	type;
	क्रमागत via_port_mode	mode;
	u16			io_port;
	u8			ioport_index;
पूर्ण;

/*
 * Allow subdevs to रेजिस्टर suspend/resume hooks.
 */
काष्ठा viafb_pm_hooks अणु
	काष्ठा list_head list;
	पूर्णांक (*suspend)(व्योम *निजी);
	पूर्णांक (*resume)(व्योम *निजी);
	व्योम *निजी;
पूर्ण;

व्योम viafb_pm_रेजिस्टर(काष्ठा viafb_pm_hooks *hooks);
व्योम viafb_pm_unरेजिस्टर(काष्ठा viafb_pm_hooks *hooks);

/*
 * This is the global viafb "device" containing stuff needed by
 * all subdevs.
 */
काष्ठा viafb_dev अणु
	काष्ठा pci_dev *pdev;
	पूर्णांक chip_type;
	काष्ठा via_port_cfg *port_cfg;
	/*
	 * Spinlock क्रम access to device रेजिस्टरs.  Not yet
	 * globally used.
	 */
	spinlock_t reg_lock;
	/*
	 * The framebuffer MMIO region.  Little, अगर anything, touches
	 * this memory directly, and certainly nothing outside of the
	 * framebuffer device itself.  We *करो* have to be able to allocate
	 * chunks of this memory क्रम other devices, though.
	 */
	अचिन्हित दीर्घ fbmem_start;
	दीर्घ fbmem_len;
	व्योम __iomem *fbmem;
#अगर defined(CONFIG_VIDEO_VIA_CAMERA) || defined(CONFIG_VIDEO_VIA_CAMERA_MODULE)
	दीर्घ camera_fbmem_offset;
	दीर्घ camera_fbmem_size;
#पूर्ण_अगर
	/*
	 * The MMIO region क्रम device रेजिस्टरs.
	 */
	अचिन्हित दीर्घ engine_start;
	अचिन्हित दीर्घ engine_len;
	व्योम __iomem *engine_mmio;

पूर्ण;

/*
 * Interrupt management.
 */

व्योम viafb_irq_enable(u32 mask);
व्योम viafb_irq_disable(u32 mask);

/*
 * The global पूर्णांकerrupt control रेजिस्टर and its bits.
 */
#घोषणा VDE_INTERRUPT	0x200	/* Video पूर्णांकerrupt flags/masks */
#घोषणा   VDE_I_DVISENSE  0x00000001  /* DVI sense पूर्णांक status */
#घोषणा   VDE_I_VBLANK    0x00000002  /* Vertical blank status */
#घोषणा   VDE_I_MCCFI	  0x00000004  /* MCE compl. frame पूर्णांक status */
#घोषणा   VDE_I_VSYNC	  0x00000008  /* VGA VSYNC पूर्णांक status */
#घोषणा   VDE_I_DMA0DDONE 0x00000010  /* DMA 0 descr करोne */
#घोषणा   VDE_I_DMA0TDONE 0x00000020  /* DMA 0 transfer करोne */
#घोषणा   VDE_I_DMA1DDONE 0x00000040  /* DMA 1 descr करोne */
#घोषणा   VDE_I_DMA1TDONE 0x00000080  /* DMA 1 transfer करोne */
#घोषणा   VDE_I_C1AV      0x00000100  /* Cap Eng 1 act vid end */
#घोषणा   VDE_I_HQV0	  0x00000200  /* First HQV engine */
#घोषणा   VDE_I_HQV1      0x00000400  /* Second HQV engine */
#घोषणा   VDE_I_HQV1EN	  0x00000800  /* Second HQV engine enable */
#घोषणा   VDE_I_C0AV      0x00001000  /* Cap Eng 0 act vid end */
#घोषणा   VDE_I_C0VBI     0x00002000  /* Cap Eng 0 VBI end */
#घोषणा   VDE_I_C1VBI     0x00004000  /* Cap Eng 1 VBI end */
#घोषणा   VDE_I_VSYNC2    0x00008000  /* Sec. Disp. VSYNC */
#घोषणा   VDE_I_DVISNSEN  0x00010000  /* DVI sense enable */
#घोषणा   VDE_I_VSYNC2EN  0x00020000  /* Sec Disp VSYNC enable */
#घोषणा   VDE_I_MCCFIEN	  0x00040000  /* MC comp frame पूर्णांक mask enable */
#घोषणा   VDE_I_VSYNCEN   0x00080000  /* VSYNC enable */
#घोषणा   VDE_I_DMA0DDEN  0x00100000  /* DMA 0 descr करोne enable */
#घोषणा   VDE_I_DMA0TDEN  0x00200000  /* DMA 0 trans करोne enable */
#घोषणा   VDE_I_DMA1DDEN  0x00400000  /* DMA 1 descr करोne enable */
#घोषणा   VDE_I_DMA1TDEN  0x00800000  /* DMA 1 trans करोne enable */
#घोषणा   VDE_I_C1AVEN    0x01000000  /* cap 1 act vid end enable */
#घोषणा   VDE_I_HQV0EN	  0x02000000  /* First hqv engine enable */
#घोषणा   VDE_I_C1VBIEN	  0x04000000  /* Cap 1 VBI end enable */
#घोषणा   VDE_I_LVDSSI    0x08000000  /* LVDS sense पूर्णांकerrupt */
#घोषणा   VDE_I_C0AVEN    0x10000000  /* Cap 0 act vid end enable */
#घोषणा   VDE_I_C0VBIEN   0x20000000  /* Cap 0 VBI end enable */
#घोषणा   VDE_I_LVDSSIEN  0x40000000  /* LVDS Sense enable */
#घोषणा   VDE_I_ENABLE	  0x80000000  /* Global पूर्णांकerrupt enable */

#अगर defined(CONFIG_VIDEO_VIA_CAMERA) || defined(CONFIG_VIDEO_VIA_CAMERA_MODULE)
/*
 * DMA management.
 */
पूर्णांक viafb_request_dma(व्योम);
व्योम viafb_release_dma(व्योम);
/* व्योम viafb_dma_copy_out(अचिन्हित पूर्णांक offset, dma_addr_t paddr, पूर्णांक len); */
पूर्णांक viafb_dma_copy_out_sg(अचिन्हित पूर्णांक offset, काष्ठा scatterlist *sg, पूर्णांक nsg);

/*
 * DMA Controller रेजिस्टरs.
 */
#घोषणा VDMA_MR0	0xe00		/* Mod reg 0 */
#घोषणा   VDMA_MR_CHAIN   0x01		/* Chaining mode */
#घोषणा   VDMA_MR_TDIE    0x02		/* Transfer करोne पूर्णांक enable */
#घोषणा VDMA_CSR0	0xe04		/* Control/status */
#घोषणा	  VDMA_C_ENABLE	  0x01		  /* DMA Enable */
#घोषणा	  VDMA_C_START	  0x02		  /* Start a transfer */
#घोषणा	  VDMA_C_ABORT	  0x04		  /* Abort a transfer */
#घोषणा	  VDMA_C_DONE	  0x08		  /* Transfer is करोne */
#घोषणा VDMA_MARL0	0xe20		/* Mem addr low */
#घोषणा VDMA_MARH0	0xe24		/* Mem addr high */
#घोषणा VDMA_DAR0	0xe28		/* Device address */
#घोषणा VDMA_DQWCR0	0xe2c		/* Count (16-byte) */
#घोषणा VDMA_TMR0	0xe30		/* Tile mode reg */
#घोषणा VDMA_DPRL0	0xe34		/* Not sure */
#घोषणा	  VDMA_DPR_IN	  0x08		/* Inbound transfer to FB */
#घोषणा VDMA_DPRH0	0xe38
#घोषणा VDMA_PMR0	(0xe00 + 0x134) /* Pitch mode */

/*
 * Useful stuff that probably beदीर्घs somewhere global.
 */
#घोषणा VGA_WIDTH	640
#घोषणा VGA_HEIGHT	480
#पूर्ण_अगर /* CONFIG_VIDEO_VIA_CAMERA */

/*
 * Indexed port operations.  Note that these are all multi-op
 * functions; every invocation will be racy अगर you're not holding
 * reg_lock.
 */

#घोषणा VIAStatus   0x3DA  /* Non-indexed port */
#घोषणा VIACR       0x3D4
#घोषणा VIASR       0x3C4
#घोषणा VIAGR       0x3CE
#घोषणा VIAAR       0x3C0

अटल अंतरभूत u8 via_पढ़ो_reg(u16 port, u8 index)
अणु
	outb(index, port);
	वापस inb(port + 1);
पूर्ण

अटल अंतरभूत व्योम via_ग_लिखो_reg(u16 port, u8 index, u8 data)
अणु
	outb(index, port);
	outb(data, port + 1);
पूर्ण

अटल अंतरभूत व्योम via_ग_लिखो_reg_mask(u16 port, u8 index, u8 data, u8 mask)
अणु
	u8 old;

	outb(index, port);
	old = inb(port + 1);
	outb((data & mask) | (old & ~mask), port + 1);
पूर्ण

#घोषणा VIA_MISC_REG_READ	0x03CC
#घोषणा VIA_MISC_REG_WRITE	0x03C2

अटल अंतरभूत व्योम via_ग_लिखो_misc_reg_mask(u8 data, u8 mask)
अणु
	u8 old = inb(VIA_MISC_REG_READ);
	outb((data & mask) | (old & ~mask), VIA_MISC_REG_WRITE);
पूर्ण


#पूर्ण_अगर /* __VIA_CORE_H__ */
