<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SVGA_H
#घोषणा _LINUX_SVGA_H

#समावेश <linux/pci.h>
#समावेश <video/vga.h>

/* Terminator क्रम रेजिस्टर set */

#घोषणा VGA_REGSET_END_VAL	0xFF
#घोषणा VGA_REGSET_END		अणुVGA_REGSET_END_VAL, 0, 0पूर्ण

काष्ठा vga_regset अणु
	u8 regnum;
	u8 lowbit;
	u8 highbit;
पूर्ण;

/* ------------------------------------------------------------------------- */

#घोषणा SVGA_FORMAT_END_VAL	0xFFFF
#घोषणा SVGA_FORMAT_END		अणुSVGA_FORMAT_END_VAL, अणु0, 0, 0पूर्ण, अणु0, 0, 0पूर्ण, अणु0, 0, 0पूर्ण, अणु0, 0, 0पूर्ण, 0, 0, 0, 0, 0, 0पूर्ण

काष्ठा svga_fb_क्रमmat अणु
	/* var part */
	u32 bits_per_pixel;
	काष्ठा fb_bitfield red;
	काष्ठा fb_bitfield green;
	काष्ठा fb_bitfield blue;
	काष्ठा fb_bitfield transp;
	u32 nonstd;
	/* fix part */
	u32 type;
	u32 type_aux;
	u32 visual;
	u32 xpanstep;
	u32 xresstep;
पूर्ण;

काष्ठा svga_timing_regs अणु
	स्थिर काष्ठा vga_regset *h_total_regs;
	स्थिर काष्ठा vga_regset *h_display_regs;
	स्थिर काष्ठा vga_regset *h_blank_start_regs;
	स्थिर काष्ठा vga_regset *h_blank_end_regs;
	स्थिर काष्ठा vga_regset *h_sync_start_regs;
	स्थिर काष्ठा vga_regset *h_sync_end_regs;

	स्थिर काष्ठा vga_regset *v_total_regs;
	स्थिर काष्ठा vga_regset *v_display_regs;
	स्थिर काष्ठा vga_regset *v_blank_start_regs;
	स्थिर काष्ठा vga_regset *v_blank_end_regs;
	स्थिर काष्ठा vga_regset *v_sync_start_regs;
	स्थिर काष्ठा vga_regset *v_sync_end_regs;
पूर्ण;

काष्ठा svga_pll अणु
	u16 m_min;
	u16 m_max;
	u16 n_min;
	u16 n_max;
	u16 r_min;
	u16 r_max;  /* r_max < 32 */
	u32 f_vco_min;
	u32 f_vco_max;
	u32 f_base;
पूर्ण;


/* Write a value to the attribute रेजिस्टर */

अटल अंतरभूत व्योम svga_wattr(व्योम __iomem *regbase, u8 index, u8 data)
अणु
	vga_r(regbase, VGA_IS1_RC);
	vga_w(regbase, VGA_ATT_IW, index);
	vga_w(regbase, VGA_ATT_W, data);
पूर्ण

/* Write a value to a sequence रेजिस्टर with a mask */

अटल अंतरभूत व्योम svga_wseq_mask(व्योम __iomem *regbase, u8 index, u8 data, u8 mask)
अणु
	vga_wseq(regbase, index, (data & mask) | (vga_rseq(regbase, index) & ~mask));
पूर्ण

/* Write a value to a CRT रेजिस्टर with a mask */

अटल अंतरभूत व्योम svga_wcrt_mask(व्योम __iomem *regbase, u8 index, u8 data, u8 mask)
अणु
	vga_wcrt(regbase, index, (data & mask) | (vga_rcrt(regbase, index) & ~mask));
पूर्ण

अटल अंतरभूत पूर्णांक svga_primary_device(काष्ठा pci_dev *dev)
अणु
	u16 flags;
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &flags);
	वापस (flags & PCI_COMMAND_IO);
पूर्ण


व्योम svga_wcrt_multi(व्योम __iomem *regbase, स्थिर काष्ठा vga_regset *regset, u32 value);
व्योम svga_wseq_multi(व्योम __iomem *regbase, स्थिर काष्ठा vga_regset *regset, u32 value);

व्योम svga_set_शेष_gfx_regs(व्योम __iomem *regbase);
व्योम svga_set_शेष_atc_regs(व्योम __iomem *regbase);
व्योम svga_set_शेष_seq_regs(व्योम __iomem *regbase);
व्योम svga_set_शेष_crt_regs(व्योम __iomem *regbase);
व्योम svga_set_texपंचांगode_vga_regs(व्योम __iomem *regbase);

व्योम svga_settile(काष्ठा fb_info *info, काष्ठा fb_tilemap *map);
व्योम svga_tilecopy(काष्ठा fb_info *info, काष्ठा fb_tilearea *area);
व्योम svga_tilefill(काष्ठा fb_info *info, काष्ठा fb_tilerect *rect);
व्योम svga_tileblit(काष्ठा fb_info *info, काष्ठा fb_tileblit *blit);
व्योम svga_tilecursor(व्योम __iomem *regbase, काष्ठा fb_info *info, काष्ठा fb_tilecursor *cursor);
पूर्णांक svga_get_tilemax(काष्ठा fb_info *info);
व्योम svga_get_caps(काष्ठा fb_info *info, काष्ठा fb_blit_caps *caps,
		   काष्ठा fb_var_screeninfo *var);

पूर्णांक svga_compute_pll(स्थिर काष्ठा svga_pll *pll, u32 f_wanted, u16 *m, u16 *n, u16 *r, पूर्णांक node);
पूर्णांक svga_check_timings(स्थिर काष्ठा svga_timing_regs *पंचांग, काष्ठा fb_var_screeninfo *var, पूर्णांक node);
व्योम svga_set_timings(व्योम __iomem *regbase, स्थिर काष्ठा svga_timing_regs *पंचांग, काष्ठा fb_var_screeninfo *var, u32 hmul, u32 hभाग, u32 vmul, u32 vभाग, u32 hborder, पूर्णांक node);

पूर्णांक svga_match_क्रमmat(स्थिर काष्ठा svga_fb_क्रमmat *frm, काष्ठा fb_var_screeninfo *var, काष्ठा fb_fix_screeninfo *fix);

#पूर्ण_अगर /* _LINUX_SVGA_H */

