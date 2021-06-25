<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors: Dave Airlie <airlied@redhat.com>
 */
#अगर_अघोषित __AST_DRV_H__
#घोषणा __AST_DRV_H__

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/पन.स>
#समावेश <linux/types.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_fb_helper.h>

#घोषणा DRIVER_AUTHOR		"Dave Airlie"

#घोषणा DRIVER_NAME		"ast"
#घोषणा DRIVER_DESC		"AST"
#घोषणा DRIVER_DATE		"20120228"

#घोषणा DRIVER_MAJOR		0
#घोषणा DRIVER_MINOR		1
#घोषणा DRIVER_PATCHLEVEL	0

#घोषणा PCI_CHIP_AST2000 0x2000
#घोषणा PCI_CHIP_AST2100 0x2010


क्रमागत ast_chip अणु
	AST2000,
	AST2100,
	AST1100,
	AST2200,
	AST2150,
	AST2300,
	AST2400,
	AST2500,
	AST2600,
पूर्ण;

क्रमागत ast_tx_chip अणु
	AST_TX_NONE,
	AST_TX_SIL164,
	AST_TX_ITE66121,
	AST_TX_DP501,
पूर्ण;

#घोषणा AST_DRAM_512Mx16 0
#घोषणा AST_DRAM_1Gx16   1
#घोषणा AST_DRAM_512Mx32 2
#घोषणा AST_DRAM_1Gx32   3
#घोषणा AST_DRAM_2Gx16   6
#घोषणा AST_DRAM_4Gx16   7
#घोषणा AST_DRAM_8Gx16   8

/*
 * Cursor plane
 */

#घोषणा AST_MAX_HWC_WIDTH	64
#घोषणा AST_MAX_HWC_HEIGHT	64

#घोषणा AST_HWC_SIZE		(AST_MAX_HWC_WIDTH * AST_MAX_HWC_HEIGHT * 2)
#घोषणा AST_HWC_SIGNATURE_SIZE	32

#घोषणा AST_DEFAULT_HWC_NUM	2

/* define क्रम signature काष्ठाure */
#घोषणा AST_HWC_SIGNATURE_CHECKSUM	0x00
#घोषणा AST_HWC_SIGNATURE_SizeX		0x04
#घोषणा AST_HWC_SIGNATURE_SizeY		0x08
#घोषणा AST_HWC_SIGNATURE_X		0x0C
#घोषणा AST_HWC_SIGNATURE_Y		0x10
#घोषणा AST_HWC_SIGNATURE_HOTSPOTX	0x14
#घोषणा AST_HWC_SIGNATURE_HOTSPOTY	0x18

काष्ठा ast_cursor_plane अणु
	काष्ठा drm_plane base;

	काष्ठा अणु
		काष्ठा drm_gem_vram_object *gbo;
		काष्ठा dma_buf_map map;
		u64 off;
	पूर्ण hwc[AST_DEFAULT_HWC_NUM];

	अचिन्हित पूर्णांक next_hwc_index;
पूर्ण;

अटल अंतरभूत काष्ठा ast_cursor_plane *
to_ast_cursor_plane(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा ast_cursor_plane, base);
पूर्ण

/*
 * Connector with i2c channel
 */

काष्ठा ast_i2c_chan अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा drm_device *dev;
	काष्ठा i2c_algo_bit_data bit;
पूर्ण;

काष्ठा ast_connector अणु
	काष्ठा drm_connector base;
	काष्ठा ast_i2c_chan *i2c;
पूर्ण;

अटल अंतरभूत काष्ठा ast_connector *
to_ast_connector(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा ast_connector, base);
पूर्ण

/*
 * Device
 */

काष्ठा ast_निजी अणु
	काष्ठा drm_device base;

	व्योम __iomem *regs;
	व्योम __iomem *ioregs;

	क्रमागत ast_chip chip;
	bool vga2_clone;
	uपूर्णांक32_t dram_bus_width;
	uपूर्णांक32_t dram_type;
	uपूर्णांक32_t mclk;

	पूर्णांक fb_mtrr;

	काष्ठा drm_plane primary_plane;
	काष्ठा ast_cursor_plane cursor_plane;
	काष्ठा drm_crtc crtc;
	काष्ठा drm_encoder encoder;
	काष्ठा ast_connector connector;

	bool support_wide_screen;
	क्रमागत अणु
		ast_use_p2a,
		ast_use_dt,
		ast_use_शेषs
	पूर्ण config_mode;

	क्रमागत ast_tx_chip tx_chip_type;
	u8 dp501_maxclk;
	u8 *dp501_fw_addr;
	स्थिर काष्ठा firmware *dp501_fw;	/* dp501 fw */
पूर्ण;

अटल अंतरभूत काष्ठा ast_निजी *to_ast_निजी(काष्ठा drm_device *dev)
अणु
	वापस container_of(dev, काष्ठा ast_निजी, base);
पूर्ण

काष्ठा ast_निजी *ast_device_create(स्थिर काष्ठा drm_driver *drv,
				      काष्ठा pci_dev *pdev,
				      अचिन्हित दीर्घ flags);

#घोषणा AST_IO_AR_PORT_WRITE		(0x40)
#घोषणा AST_IO_MISC_PORT_WRITE		(0x42)
#घोषणा AST_IO_VGA_ENABLE_PORT		(0x43)
#घोषणा AST_IO_SEQ_PORT			(0x44)
#घोषणा AST_IO_DAC_INDEX_READ		(0x47)
#घोषणा AST_IO_DAC_INDEX_WRITE		(0x48)
#घोषणा AST_IO_DAC_DATA		        (0x49)
#घोषणा AST_IO_GR_PORT			(0x4E)
#घोषणा AST_IO_CRTC_PORT		(0x54)
#घोषणा AST_IO_INPUT_STATUS1_READ	(0x5A)
#घोषणा AST_IO_MISC_PORT_READ		(0x4C)

#घोषणा AST_IO_MM_OFFSET		(0x380)

#घोषणा AST_IO_VGAIR1_VREFRESH		BIT(3)

#घोषणा AST_IO_VGACRCB_HWC_ENABLED     BIT(1)
#घोषणा AST_IO_VGACRCB_HWC_16BPP       BIT(0) /* set: ARGB4444, cleared: 2bpp palette */

#घोषणा __ast_पढ़ो(x) \
अटल अंतरभूत u##x ast_पढ़ो##x(काष्ठा ast_निजी *ast, u32 reg) अणु \
u##x val = 0;\
val = ioपढ़ो##x(ast->regs + reg); \
वापस val;\
पूर्ण

__ast_पढ़ो(8);
__ast_पढ़ो(16);
__ast_पढ़ो(32)

#घोषणा __ast_io_पढ़ो(x) \
अटल अंतरभूत u##x ast_io_पढ़ो##x(काष्ठा ast_निजी *ast, u32 reg) अणु \
u##x val = 0;\
val = ioपढ़ो##x(ast->ioregs + reg); \
वापस val;\
पूर्ण

__ast_io_पढ़ो(8);
__ast_io_पढ़ो(16);
__ast_io_पढ़ो(32);

#घोषणा __ast_ग_लिखो(x) \
अटल अंतरभूत व्योम ast_ग_लिखो##x(काष्ठा ast_निजी *ast, u32 reg, u##x val) अणु\
	ioग_लिखो##x(val, ast->regs + reg);\
	पूर्ण

__ast_ग_लिखो(8);
__ast_ग_लिखो(16);
__ast_ग_लिखो(32);

#घोषणा __ast_io_ग_लिखो(x) \
अटल अंतरभूत व्योम ast_io_ग_लिखो##x(काष्ठा ast_निजी *ast, u32 reg, u##x val) अणु\
	ioग_लिखो##x(val, ast->ioregs + reg);\
	पूर्ण

__ast_io_ग_लिखो(8);
__ast_io_ग_लिखो(16);
#अघोषित __ast_io_ग_लिखो

अटल अंतरभूत व्योम ast_set_index_reg(काष्ठा ast_निजी *ast,
				     uपूर्णांक32_t base, uपूर्णांक8_t index,
				     uपूर्णांक8_t val)
अणु
	ast_io_ग_लिखो16(ast, base, ((u16)val << 8) | index);
पूर्ण

व्योम ast_set_index_reg_mask(काष्ठा ast_निजी *ast,
			    uपूर्णांक32_t base, uपूर्णांक8_t index,
			    uपूर्णांक8_t mask, uपूर्णांक8_t val);
uपूर्णांक8_t ast_get_index_reg(काष्ठा ast_निजी *ast,
			  uपूर्णांक32_t base, uपूर्णांक8_t index);
uपूर्णांक8_t ast_get_index_reg_mask(काष्ठा ast_निजी *ast,
			       uपूर्णांक32_t base, uपूर्णांक8_t index, uपूर्णांक8_t mask);

अटल अंतरभूत व्योम ast_खोलो_key(काष्ठा ast_निजी *ast)
अणु
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x80, 0xA8);
पूर्ण

#घोषणा AST_VIDMEM_SIZE_8M    0x00800000
#घोषणा AST_VIDMEM_SIZE_16M   0x01000000
#घोषणा AST_VIDMEM_SIZE_32M   0x02000000
#घोषणा AST_VIDMEM_SIZE_64M   0x04000000
#घोषणा AST_VIDMEM_SIZE_128M  0x08000000

#घोषणा AST_VIDMEM_DEFAULT_SIZE AST_VIDMEM_SIZE_8M

काष्ठा ast_vbios_stdtable अणु
	u8 misc;
	u8 seq[4];
	u8 crtc[25];
	u8 ar[20];
	u8 gr[9];
पूर्ण;

काष्ठा ast_vbios_enhtable अणु
	u32 ht;
	u32 hde;
	u32 hfp;
	u32 hsync;
	u32 vt;
	u32 vde;
	u32 vfp;
	u32 vsync;
	u32 dclk_index;
	u32 flags;
	u32 refresh_rate;
	u32 refresh_rate_index;
	u32 mode_id;
पूर्ण;

काष्ठा ast_vbios_dclk_info अणु
	u8 param1;
	u8 param2;
	u8 param3;
पूर्ण;

काष्ठा ast_vbios_mode_info अणु
	स्थिर काष्ठा ast_vbios_stdtable *std_table;
	स्थिर काष्ठा ast_vbios_enhtable *enh_table;
पूर्ण;

काष्ठा ast_crtc_state अणु
	काष्ठा drm_crtc_state base;

	/* Last known क्रमmat of primary plane */
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat;

	काष्ठा ast_vbios_mode_info vbios_mode_info;
पूर्ण;

#घोषणा to_ast_crtc_state(state) container_of(state, काष्ठा ast_crtc_state, base)

पूर्णांक ast_mode_config_init(काष्ठा ast_निजी *ast);

#घोषणा AST_MM_ALIGN_SHIFT 4
#घोषणा AST_MM_ALIGN_MASK ((1 << AST_MM_ALIGN_SHIFT) - 1)

पूर्णांक ast_mm_init(काष्ठा ast_निजी *ast);

/* ast post */
व्योम ast_enable_vga(काष्ठा drm_device *dev);
व्योम ast_enable_mmio(काष्ठा drm_device *dev);
bool ast_is_vga_enabled(काष्ठा drm_device *dev);
व्योम ast_post_gpu(काष्ठा drm_device *dev);
u32 ast_mindwm(काष्ठा ast_निजी *ast, u32 r);
व्योम ast_moutdwm(काष्ठा ast_निजी *ast, u32 r, u32 v);
/* ast dp501 */
व्योम ast_set_dp501_video_output(काष्ठा drm_device *dev, u8 mode);
bool ast_backup_fw(काष्ठा drm_device *dev, u8 *addr, u32 size);
bool ast_dp501_पढ़ो_edid(काष्ठा drm_device *dev, u8 *ediddata);
u8 ast_get_dp501_max_clk(काष्ठा drm_device *dev);
व्योम ast_init_3rdtx(काष्ठा drm_device *dev);

#पूर्ण_अगर
