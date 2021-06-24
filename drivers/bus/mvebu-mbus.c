<शैली गुरु>
/*
 * Address map functions क्रम Marvell EBU SoCs (Kirkwood, Armada
 * 370/XP, Dove, Orion5x and MV78xx0)
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * The Marvell EBU SoCs have a configurable physical address space:
 * the physical address at which certain devices (PCIe, NOR, न_अंकD,
 * etc.) sit can be configured. The configuration takes place through
 * two sets of रेजिस्टरs:
 *
 * - One to configure the access of the CPU to the devices. Depending
 *   on the families, there are between 8 and 20 configurable winकरोws,
 *   each can be use to create a physical memory winकरोw that maps to a
 *   specअगरic device. Devices are identअगरied by a tuple (target,
 *   attribute).
 *
 * - One to configure the access to the CPU to the SDRAM. There are
 *   either 2 (क्रम Dove) or 4 (क्रम other families) winकरोws to map the
 *   SDRAM पूर्णांकo the physical address space.
 *
 * This driver:
 *
 * - Reads out the SDRAM address decoding winकरोws at initialization
 *   समय, and fills the mvebu_mbus_dram_info काष्ठाure with these
 *   inक्रमmations. The exported function mv_mbus_dram_info() allow
 *   device drivers to get those inक्रमmations related to the SDRAM
 *   address decoding winकरोws. This is because devices also have their
 *   own winकरोws (configured through रेजिस्टरs that are part of each
 *   device रेजिस्टर space), and thereक्रमe the drivers क्रम Marvell
 *   devices have to configure those device -> SDRAM winकरोws to ensure
 *   that DMA works properly.
 *
 * - Provides an API क्रम platक्रमm code or device drivers to
 *   dynamically add or हटाओ address decoding winकरोws क्रम the CPU ->
 *   device accesses. This API is mvebu_mbus_add_winकरोw_by_id(),
 *   mvebu_mbus_add_winकरोw_remap_by_id() and
 *   mvebu_mbus_del_winकरोw().
 *
 * - Provides a debugfs पूर्णांकerface in /sys/kernel/debug/mvebu-mbus/ to
 *   see the list of CPU -> SDRAM winकरोws and their configuration
 *   (file 'sdram') and the list of CPU -> devices winकरोws and their
 *   configuration (file 'devices').
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mbus.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/log2.h>
#समावेश <linux/memblock.h>
#समावेश <linux/syscore_ops.h>

/*
 * DDR target is the same on all platक्रमms.
 */
#घोषणा TARGET_DDR		0

/*
 * CPU Address Decode Winकरोws रेजिस्टरs
 */
#घोषणा WIN_CTRL_OFF		0x0000
#घोषणा   WIN_CTRL_ENABLE       BIT(0)
/* Only on HW I/O coherency capable platक्रमms */
#घोषणा   WIN_CTRL_SYNCBARRIER  BIT(1)
#घोषणा   WIN_CTRL_TGT_MASK     0xf0
#घोषणा   WIN_CTRL_TGT_SHIFT    4
#घोषणा   WIN_CTRL_ATTR_MASK    0xff00
#घोषणा   WIN_CTRL_ATTR_SHIFT   8
#घोषणा   WIN_CTRL_SIZE_MASK    0xffff0000
#घोषणा   WIN_CTRL_SIZE_SHIFT   16
#घोषणा WIN_BASE_OFF		0x0004
#घोषणा   WIN_BASE_LOW          0xffff0000
#घोषणा   WIN_BASE_HIGH         0xf
#घोषणा WIN_REMAP_LO_OFF	0x0008
#घोषणा   WIN_REMAP_LOW         0xffff0000
#घोषणा WIN_REMAP_HI_OFF	0x000c

#घोषणा UNIT_SYNC_BARRIER_OFF   0x84
#घोषणा   UNIT_SYNC_BARRIER_ALL 0xFFFF

#घोषणा ATTR_HW_COHERENCY	(0x1 << 4)

#घोषणा DDR_BASE_CS_OFF(n)	(0x0000 + ((n) << 3))
#घोषणा  DDR_BASE_CS_HIGH_MASK  0xf
#घोषणा  DDR_BASE_CS_LOW_MASK   0xff000000
#घोषणा DDR_SIZE_CS_OFF(n)	(0x0004 + ((n) << 3))
#घोषणा  DDR_SIZE_ENABLED       BIT(0)
#घोषणा  DDR_SIZE_CS_MASK       0x1c
#घोषणा  DDR_SIZE_CS_SHIFT      2
#घोषणा  DDR_SIZE_MASK          0xff000000

#घोषणा DOVE_DDR_BASE_CS_OFF(n) ((n) << 4)

/* Relative to mbusbridge_base */
#घोषणा MBUS_BRIDGE_CTRL_OFF	0x0
#घोषणा MBUS_BRIDGE_BASE_OFF	0x4

/* Maximum number of winकरोws, क्रम all known platक्रमms */
#घोषणा MBUS_WINS_MAX           20

काष्ठा mvebu_mbus_state;

काष्ठा mvebu_mbus_soc_data अणु
	अचिन्हित पूर्णांक num_wins;
	bool has_mbus_bridge;
	अचिन्हित पूर्णांक (*win_cfg_offset)(स्थिर पूर्णांक win);
	अचिन्हित पूर्णांक (*win_remap_offset)(स्थिर पूर्णांक win);
	व्योम (*setup_cpu_target)(काष्ठा mvebu_mbus_state *s);
	पूर्णांक (*save_cpu_target)(काष्ठा mvebu_mbus_state *s,
			       u32 __iomem *store_addr);
	पूर्णांक (*show_cpu_target)(काष्ठा mvebu_mbus_state *s,
			       काष्ठा seq_file *seq, व्योम *v);
पूर्ण;

/*
 * Used to store the state of one MBus winकरोw accross suspend/resume.
 */
काष्ठा mvebu_mbus_win_data अणु
	u32 ctrl;
	u32 base;
	u32 remap_lo;
	u32 remap_hi;
पूर्ण;

काष्ठा mvebu_mbus_state अणु
	व्योम __iomem *mbuswins_base;
	व्योम __iomem *sdramwins_base;
	व्योम __iomem *mbusbridge_base;
	phys_addr_t sdramwins_phys_base;
	काष्ठा dentry *debugfs_root;
	काष्ठा dentry *debugfs_sdram;
	काष्ठा dentry *debugfs_devs;
	काष्ठा resource pcie_mem_aperture;
	काष्ठा resource pcie_io_aperture;
	स्थिर काष्ठा mvebu_mbus_soc_data *soc;
	पूर्णांक hw_io_coherency;

	/* Used during suspend/resume */
	u32 mbus_bridge_ctrl;
	u32 mbus_bridge_base;
	काष्ठा mvebu_mbus_win_data wins[MBUS_WINS_MAX];
पूर्ण;

अटल काष्ठा mvebu_mbus_state mbus_state;

/*
 * We provide two variants of the mv_mbus_dram_info() function:
 *
 * - The normal one, where the described DRAM ranges may overlap with
 *   the I/O winकरोws, but क्रम which the DRAM ranges are guaranteed to
 *   have a घातer of two size. Such ranges are suitable क्रम the DMA
 *   masters that only DMA between the RAM and the device, which is
 *   actually all devices except the crypto engines.
 *
 * - The 'nooverlap' one, where the described DRAM ranges are
 *   guaranteed to not overlap with the I/O winकरोws, but क्रम which the
 *   DRAM ranges will not have घातer of two sizes. They will only be
 *   aligned on a 64 KB boundary, and have a size multiple of 64
 *   KB. Such ranges are suitable क्रम the DMA masters that DMA between
 *   the crypto SRAM (which is mapped through an I/O winकरोw) and a
 *   device. This is the हाल क्रम the crypto engines.
 */

अटल काष्ठा mbus_dram_target_info mvebu_mbus_dram_info;
अटल काष्ठा mbus_dram_target_info mvebu_mbus_dram_info_nooverlap;

स्थिर काष्ठा mbus_dram_target_info *mv_mbus_dram_info(व्योम)
अणु
	वापस &mvebu_mbus_dram_info;
पूर्ण
EXPORT_SYMBOL_GPL(mv_mbus_dram_info);

स्थिर काष्ठा mbus_dram_target_info *mv_mbus_dram_info_nooverlap(व्योम)
अणु
	वापस &mvebu_mbus_dram_info_nooverlap;
पूर्ण
EXPORT_SYMBOL_GPL(mv_mbus_dram_info_nooverlap);

/* Checks whether the given winकरोw has remap capability */
अटल bool mvebu_mbus_winकरोw_is_remappable(काष्ठा mvebu_mbus_state *mbus,
					    स्थिर पूर्णांक win)
अणु
	वापस mbus->soc->win_remap_offset(win) != MVEBU_MBUS_NO_REMAP;
पूर्ण

/*
 * Functions to manipulate the address decoding winकरोws
 */

अटल व्योम mvebu_mbus_पढ़ो_winकरोw(काष्ठा mvebu_mbus_state *mbus,
				   पूर्णांक win, पूर्णांक *enabled, u64 *base,
				   u32 *size, u8 *target, u8 *attr,
				   u64 *remap)
अणु
	व्योम __iomem *addr = mbus->mbuswins_base +
		mbus->soc->win_cfg_offset(win);
	u32 basereg = पढ़ोl(addr + WIN_BASE_OFF);
	u32 ctrlreg = पढ़ोl(addr + WIN_CTRL_OFF);

	अगर (!(ctrlreg & WIN_CTRL_ENABLE)) अणु
		*enabled = 0;
		वापस;
	पूर्ण

	*enabled = 1;
	*base = ((u64)basereg & WIN_BASE_HIGH) << 32;
	*base |= (basereg & WIN_BASE_LOW);
	*size = (ctrlreg | ~WIN_CTRL_SIZE_MASK) + 1;

	अगर (target)
		*target = (ctrlreg & WIN_CTRL_TGT_MASK) >> WIN_CTRL_TGT_SHIFT;

	अगर (attr)
		*attr = (ctrlreg & WIN_CTRL_ATTR_MASK) >> WIN_CTRL_ATTR_SHIFT;

	अगर (remap) अणु
		अगर (mvebu_mbus_winकरोw_is_remappable(mbus, win)) अणु
			u32 remap_low, remap_hi;
			व्योम __iomem *addr_rmp = mbus->mbuswins_base +
				mbus->soc->win_remap_offset(win);
			remap_low = पढ़ोl(addr_rmp + WIN_REMAP_LO_OFF);
			remap_hi  = पढ़ोl(addr_rmp + WIN_REMAP_HI_OFF);
			*remap = ((u64)remap_hi << 32) | remap_low;
		पूर्ण अन्यथा
			*remap = 0;
	पूर्ण
पूर्ण

अटल व्योम mvebu_mbus_disable_winकरोw(काष्ठा mvebu_mbus_state *mbus,
				      पूर्णांक win)
अणु
	व्योम __iomem *addr;

	addr = mbus->mbuswins_base + mbus->soc->win_cfg_offset(win);
	ग_लिखोl(0, addr + WIN_BASE_OFF);
	ग_लिखोl(0, addr + WIN_CTRL_OFF);

	अगर (mvebu_mbus_winकरोw_is_remappable(mbus, win)) अणु
		addr = mbus->mbuswins_base + mbus->soc->win_remap_offset(win);
		ग_लिखोl(0, addr + WIN_REMAP_LO_OFF);
		ग_लिखोl(0, addr + WIN_REMAP_HI_OFF);
	पूर्ण
पूर्ण

/* Checks whether the given winकरोw number is available */

अटल पूर्णांक mvebu_mbus_winकरोw_is_मुक्त(काष्ठा mvebu_mbus_state *mbus,
				     स्थिर पूर्णांक win)
अणु
	व्योम __iomem *addr = mbus->mbuswins_base +
		mbus->soc->win_cfg_offset(win);
	u32 ctrl = पढ़ोl(addr + WIN_CTRL_OFF);

	वापस !(ctrl & WIN_CTRL_ENABLE);
पूर्ण

/*
 * Checks whether the given (base, base+size) area करोesn't overlap an
 * existing region
 */
अटल पूर्णांक mvebu_mbus_winकरोw_conflicts(काष्ठा mvebu_mbus_state *mbus,
				       phys_addr_t base, माप_प्रकार size,
				       u8 target, u8 attr)
अणु
	u64 end = (u64)base + size;
	पूर्णांक win;

	क्रम (win = 0; win < mbus->soc->num_wins; win++) अणु
		u64 wbase, wend;
		u32 wsize;
		u8 wtarget, wattr;
		पूर्णांक enabled;

		mvebu_mbus_पढ़ो_winकरोw(mbus, win,
				       &enabled, &wbase, &wsize,
				       &wtarget, &wattr, शून्य);

		अगर (!enabled)
			जारी;

		wend = wbase + wsize;

		/*
		 * Check अगर the current winकरोw overlaps with the
		 * proposed physical range
		 */
		अगर ((u64)base < wend && end > wbase)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक mvebu_mbus_find_winकरोw(काष्ठा mvebu_mbus_state *mbus,
				  phys_addr_t base, माप_प्रकार size)
अणु
	पूर्णांक win;

	क्रम (win = 0; win < mbus->soc->num_wins; win++) अणु
		u64 wbase;
		u32 wsize;
		पूर्णांक enabled;

		mvebu_mbus_पढ़ो_winकरोw(mbus, win,
				       &enabled, &wbase, &wsize,
				       शून्य, शून्य, शून्य);

		अगर (!enabled)
			जारी;

		अगर (base == wbase && size == wsize)
			वापस win;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक mvebu_mbus_setup_winकरोw(काष्ठा mvebu_mbus_state *mbus,
				   पूर्णांक win, phys_addr_t base, माप_प्रकार size,
				   phys_addr_t remap, u8 target,
				   u8 attr)
अणु
	व्योम __iomem *addr = mbus->mbuswins_base +
		mbus->soc->win_cfg_offset(win);
	u32 ctrl, remap_addr;

	अगर (!is_घातer_of_2(size)) अणु
		WARN(true, "Invalid MBus window size: 0x%zx\n", size);
		वापस -EINVAL;
	पूर्ण

	अगर ((base & (phys_addr_t)(size - 1)) != 0) अणु
		WARN(true, "Invalid MBus base/size: %pa len 0x%zx\n", &base,
		     size);
		वापस -EINVAL;
	पूर्ण

	ctrl = ((size - 1) & WIN_CTRL_SIZE_MASK) |
		(attr << WIN_CTRL_ATTR_SHIFT)    |
		(target << WIN_CTRL_TGT_SHIFT)   |
		WIN_CTRL_ENABLE;
	अगर (mbus->hw_io_coherency)
		ctrl |= WIN_CTRL_SYNCBARRIER;

	ग_लिखोl(base & WIN_BASE_LOW, addr + WIN_BASE_OFF);
	ग_लिखोl(ctrl, addr + WIN_CTRL_OFF);

	अगर (mvebu_mbus_winकरोw_is_remappable(mbus, win)) अणु
		व्योम __iomem *addr_rmp = mbus->mbuswins_base +
			mbus->soc->win_remap_offset(win);

		अगर (remap == MVEBU_MBUS_NO_REMAP)
			remap_addr = base;
		अन्यथा
			remap_addr = remap;
		ग_लिखोl(remap_addr & WIN_REMAP_LOW, addr_rmp + WIN_REMAP_LO_OFF);
		ग_लिखोl(0, addr_rmp + WIN_REMAP_HI_OFF);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_mbus_alloc_winकरोw(काष्ठा mvebu_mbus_state *mbus,
				   phys_addr_t base, माप_प्रकार size,
				   phys_addr_t remap, u8 target,
				   u8 attr)
अणु
	पूर्णांक win;

	अगर (remap == MVEBU_MBUS_NO_REMAP) अणु
		क्रम (win = 0; win < mbus->soc->num_wins; win++) अणु
			अगर (mvebu_mbus_winकरोw_is_remappable(mbus, win))
				जारी;

			अगर (mvebu_mbus_winकरोw_is_मुक्त(mbus, win))
				वापस mvebu_mbus_setup_winकरोw(mbus, win, base,
							       size, remap,
							       target, attr);
		पूर्ण
	पूर्ण

	क्रम (win = 0; win < mbus->soc->num_wins; win++) अणु
		/* Skip winकरोw अगर need remap but is not supported */
		अगर ((remap != MVEBU_MBUS_NO_REMAP) &&
		    !mvebu_mbus_winकरोw_is_remappable(mbus, win))
			जारी;

		अगर (mvebu_mbus_winकरोw_is_मुक्त(mbus, win))
			वापस mvebu_mbus_setup_winकरोw(mbus, win, base, size,
						       remap, target, attr);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

/*
 * Debugfs debugging
 */

/* Common function used क्रम Dove, Kirkwood, Armada 370/XP and Orion 5x */
अटल पूर्णांक mvebu_sdram_debug_show_orion(काष्ठा mvebu_mbus_state *mbus,
					काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		u32 basereg = पढ़ोl(mbus->sdramwins_base + DDR_BASE_CS_OFF(i));
		u32 sizereg = पढ़ोl(mbus->sdramwins_base + DDR_SIZE_CS_OFF(i));
		u64 base;
		u32 size;

		अगर (!(sizereg & DDR_SIZE_ENABLED)) अणु
			seq_म_लिखो(seq, "[%d] disabled\n", i);
			जारी;
		पूर्ण

		base = ((u64)basereg & DDR_BASE_CS_HIGH_MASK) << 32;
		base |= basereg & DDR_BASE_CS_LOW_MASK;
		size = (sizereg | ~DDR_SIZE_MASK);

		seq_म_लिखो(seq, "[%d] %016llx - %016llx : cs%d\n",
			   i, (अचिन्हित दीर्घ दीर्घ)base,
			   (अचिन्हित दीर्घ दीर्घ)base + size + 1,
			   (sizereg & DDR_SIZE_CS_MASK) >> DDR_SIZE_CS_SHIFT);
	पूर्ण

	वापस 0;
पूर्ण

/* Special function क्रम Dove */
अटल पूर्णांक mvebu_sdram_debug_show_करोve(काष्ठा mvebu_mbus_state *mbus,
				       काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		u32 map = पढ़ोl(mbus->sdramwins_base + DOVE_DDR_BASE_CS_OFF(i));
		u64 base;
		u32 size;

		अगर (!(map & 1)) अणु
			seq_म_लिखो(seq, "[%d] disabled\n", i);
			जारी;
		पूर्ण

		base = map & 0xff800000;
		size = 0x100000 << (((map & 0x000f0000) >> 16) - 4);

		seq_म_लिखो(seq, "[%d] %016llx - %016llx : cs%d\n",
			   i, (अचिन्हित दीर्घ दीर्घ)base,
			   (अचिन्हित दीर्घ दीर्घ)base + size, i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_sdram_debug_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा mvebu_mbus_state *mbus = &mbus_state;
	वापस mbus->soc->show_cpu_target(mbus, seq, v);
पूर्ण

अटल पूर्णांक mvebu_sdram_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, mvebu_sdram_debug_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations mvebu_sdram_debug_fops = अणु
	.खोलो = mvebu_sdram_debug_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक mvebu_devs_debug_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा mvebu_mbus_state *mbus = &mbus_state;
	पूर्णांक win;

	क्रम (win = 0; win < mbus->soc->num_wins; win++) अणु
		u64 wbase, wremap;
		u32 wsize;
		u8 wtarget, wattr;
		पूर्णांक enabled;

		mvebu_mbus_पढ़ो_winकरोw(mbus, win,
				       &enabled, &wbase, &wsize,
				       &wtarget, &wattr, &wremap);

		अगर (!enabled) अणु
			seq_म_लिखो(seq, "[%02d] disabled\n", win);
			जारी;
		पूर्ण

		seq_म_लिखो(seq, "[%02d] %016llx - %016llx : %04x:%04x",
			   win, (अचिन्हित दीर्घ दीर्घ)wbase,
			   (अचिन्हित दीर्घ दीर्घ)(wbase + wsize), wtarget, wattr);

		अगर (!is_घातer_of_2(wsize) ||
		    ((wbase & (u64)(wsize - 1)) != 0))
			seq_माला_दो(seq, " (Invalid base/size!!)");

		अगर (mvebu_mbus_winकरोw_is_remappable(mbus, win)) अणु
			seq_म_लिखो(seq, " (remap %016llx)\n",
				   (अचिन्हित दीर्घ दीर्घ)wremap);
		पूर्ण अन्यथा
			seq_म_लिखो(seq, "\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_devs_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, mvebu_devs_debug_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations mvebu_devs_debug_fops = अणु
	.खोलो = mvebu_devs_debug_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

/*
 * SoC-specअगरic functions and definitions
 */

अटल अचिन्हित पूर्णांक generic_mbus_win_cfg_offset(पूर्णांक win)
अणु
	वापस win << 4;
पूर्ण

अटल अचिन्हित पूर्णांक armada_370_xp_mbus_win_cfg_offset(पूर्णांक win)
अणु
	/* The रेजिस्टर layout is a bit annoying and the below code
	 * tries to cope with it.
	 * - At offset 0x0, there are the रेजिस्टरs क्रम the first 8
	 *   winकरोws, with 4 रेजिस्टरs of 32 bits per winकरोw (ctrl,
	 *   base, remap low, remap high)
	 * - Then at offset 0x80, there is a hole of 0x10 bytes क्रम
	 *   the पूर्णांकernal रेजिस्टरs base address and पूर्णांकernal units
	 *   sync barrier रेजिस्टर.
	 * - Then at offset 0x90, there the रेजिस्टरs क्रम 12
	 *   winकरोws, with only 2 रेजिस्टरs of 32 bits per winकरोw
	 *   (ctrl, base).
	 */
	अगर (win < 8)
		वापस win << 4;
	अन्यथा
		वापस 0x90 + ((win - 8) << 3);
पूर्ण

अटल अचिन्हित पूर्णांक mv78xx0_mbus_win_cfg_offset(पूर्णांक win)
अणु
	अगर (win < 8)
		वापस win << 4;
	अन्यथा
		वापस 0x900 + ((win - 8) << 4);
पूर्ण

अटल अचिन्हित पूर्णांक generic_mbus_win_remap_2_offset(पूर्णांक win)
अणु
	अगर (win < 2)
		वापस generic_mbus_win_cfg_offset(win);
	अन्यथा
		वापस MVEBU_MBUS_NO_REMAP;
पूर्ण

अटल अचिन्हित पूर्णांक generic_mbus_win_remap_4_offset(पूर्णांक win)
अणु
	अगर (win < 4)
		वापस generic_mbus_win_cfg_offset(win);
	अन्यथा
		वापस MVEBU_MBUS_NO_REMAP;
पूर्ण

अटल अचिन्हित पूर्णांक generic_mbus_win_remap_8_offset(पूर्णांक win)
अणु
	अगर (win < 8)
		वापस generic_mbus_win_cfg_offset(win);
	अन्यथा
		वापस MVEBU_MBUS_NO_REMAP;
पूर्ण

अटल अचिन्हित पूर्णांक armada_xp_mbus_win_remap_offset(पूर्णांक win)
अणु
	अगर (win < 8)
		वापस generic_mbus_win_cfg_offset(win);
	अन्यथा अगर (win == 13)
		वापस 0xF0 - WIN_REMAP_LO_OFF;
	अन्यथा
		वापस MVEBU_MBUS_NO_REMAP;
पूर्ण

/*
 * Use the memblock inक्रमmation to find the MBus bridge hole in the
 * physical address space.
 */
अटल व्योम __init
mvebu_mbus_find_bridge_hole(uपूर्णांक64_t *start, uपूर्णांक64_t *end)
अणु
	phys_addr_t reg_start, reg_end;
	uपूर्णांक64_t i, s = 0;

	क्रम_each_mem_range(i, &reg_start, &reg_end) अणु
		/*
		 * This part of the memory is above 4 GB, so we करोn't
		 * care क्रम the MBus bridge hole.
		 */
		अगर ((u64)reg_start >= 0x100000000ULL)
			जारी;

		/*
		 * The MBus bridge hole is at the end of the RAM under
		 * the 4 GB limit.
		 */
		अगर (reg_end > s)
			s = reg_end;
	पूर्ण

	*start = s;
	*end = 0x100000000ULL;
पूर्ण

/*
 * This function fills in the mvebu_mbus_dram_info_nooverlap data
 * काष्ठाure, by looking at the mvebu_mbus_dram_info data, and
 * removing the parts of it that overlap with I/O winकरोws.
 */
अटल व्योम __init
mvebu_mbus_setup_cpu_target_nooverlap(काष्ठा mvebu_mbus_state *mbus)
अणु
	uपूर्णांक64_t mbus_bridge_base, mbus_bridge_end;
	पूर्णांक cs_nooverlap = 0;
	पूर्णांक i;

	mvebu_mbus_find_bridge_hole(&mbus_bridge_base, &mbus_bridge_end);

	क्रम (i = 0; i < mvebu_mbus_dram_info.num_cs; i++) अणु
		काष्ठा mbus_dram_winकरोw *w;
		u64 base, size, end;

		w = &mvebu_mbus_dram_info.cs[i];
		base = w->base;
		size = w->size;
		end = base + size;

		/*
		 * The CS is fully enबंदd inside the MBus bridge
		 * area, so ignore it.
		 */
		अगर (base >= mbus_bridge_base && end <= mbus_bridge_end)
			जारी;

		/*
		 * Beginning of CS overlaps with end of MBus, उठाओ CS
		 * base address, and shrink its size.
		 */
		अगर (base >= mbus_bridge_base && end > mbus_bridge_end) अणु
			size -= mbus_bridge_end - base;
			base = mbus_bridge_end;
		पूर्ण

		/*
		 * End of CS overlaps with beginning of MBus, shrink
		 * CS size.
		 */
		अगर (base < mbus_bridge_base && end > mbus_bridge_base)
			size -= end - mbus_bridge_base;

		w = &mvebu_mbus_dram_info_nooverlap.cs[cs_nooverlap++];
		w->cs_index = i;
		w->mbus_attr = 0xf & ~(1 << i);
		अगर (mbus->hw_io_coherency)
			w->mbus_attr |= ATTR_HW_COHERENCY;
		w->base = base;
		w->size = size;
	पूर्ण

	mvebu_mbus_dram_info_nooverlap.mbus_dram_target_id = TARGET_DDR;
	mvebu_mbus_dram_info_nooverlap.num_cs = cs_nooverlap;
पूर्ण

अटल व्योम __init
mvebu_mbus_शेष_setup_cpu_target(काष्ठा mvebu_mbus_state *mbus)
अणु
	पूर्णांक i;
	पूर्णांक cs;

	mvebu_mbus_dram_info.mbus_dram_target_id = TARGET_DDR;

	क्रम (i = 0, cs = 0; i < 4; i++) अणु
		u32 base = पढ़ोl(mbus->sdramwins_base + DDR_BASE_CS_OFF(i));
		u32 size = पढ़ोl(mbus->sdramwins_base + DDR_SIZE_CS_OFF(i));

		/*
		 * We only take care of entries क्रम which the chip
		 * select is enabled, and that करोn't have high base
		 * address bits set (devices can only access the first
		 * 32 bits of the memory).
		 */
		अगर ((size & DDR_SIZE_ENABLED) &&
		    !(base & DDR_BASE_CS_HIGH_MASK)) अणु
			काष्ठा mbus_dram_winकरोw *w;

			w = &mvebu_mbus_dram_info.cs[cs++];
			w->cs_index = i;
			w->mbus_attr = 0xf & ~(1 << i);
			अगर (mbus->hw_io_coherency)
				w->mbus_attr |= ATTR_HW_COHERENCY;
			w->base = base & DDR_BASE_CS_LOW_MASK;
			w->size = (u64)(size | ~DDR_SIZE_MASK) + 1;
		पूर्ण
	पूर्ण
	mvebu_mbus_dram_info.num_cs = cs;
पूर्ण

अटल पूर्णांक
mvebu_mbus_शेष_save_cpu_target(काष्ठा mvebu_mbus_state *mbus,
				   u32 __iomem *store_addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		u32 base = पढ़ोl(mbus->sdramwins_base + DDR_BASE_CS_OFF(i));
		u32 size = पढ़ोl(mbus->sdramwins_base + DDR_SIZE_CS_OFF(i));

		ग_लिखोl(mbus->sdramwins_phys_base + DDR_BASE_CS_OFF(i),
		       store_addr++);
		ग_लिखोl(base, store_addr++);
		ग_लिखोl(mbus->sdramwins_phys_base + DDR_SIZE_CS_OFF(i),
		       store_addr++);
		ग_लिखोl(size, store_addr++);
	पूर्ण

	/* We've written 16 words to the store address */
	वापस 16;
पूर्ण

अटल व्योम __init
mvebu_mbus_करोve_setup_cpu_target(काष्ठा mvebu_mbus_state *mbus)
अणु
	पूर्णांक i;
	पूर्णांक cs;

	mvebu_mbus_dram_info.mbus_dram_target_id = TARGET_DDR;

	क्रम (i = 0, cs = 0; i < 2; i++) अणु
		u32 map = पढ़ोl(mbus->sdramwins_base + DOVE_DDR_BASE_CS_OFF(i));

		/*
		 * Chip select enabled?
		 */
		अगर (map & 1) अणु
			काष्ठा mbus_dram_winकरोw *w;

			w = &mvebu_mbus_dram_info.cs[cs++];
			w->cs_index = i;
			w->mbus_attr = 0; /* CS address decoding करोne inside */
					  /* the DDR controller, no need to  */
					  /* provide attributes */
			w->base = map & 0xff800000;
			w->size = 0x100000 << (((map & 0x000f0000) >> 16) - 4);
		पूर्ण
	पूर्ण

	mvebu_mbus_dram_info.num_cs = cs;
पूर्ण

अटल पूर्णांक
mvebu_mbus_करोve_save_cpu_target(काष्ठा mvebu_mbus_state *mbus,
				u32 __iomem *store_addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		u32 map = पढ़ोl(mbus->sdramwins_base + DOVE_DDR_BASE_CS_OFF(i));

		ग_लिखोl(mbus->sdramwins_phys_base + DOVE_DDR_BASE_CS_OFF(i),
		       store_addr++);
		ग_लिखोl(map, store_addr++);
	पूर्ण

	/* We've written 4 words to the store address */
	वापस 4;
पूर्ण

पूर्णांक mvebu_mbus_save_cpu_target(u32 __iomem *store_addr)
अणु
	वापस mbus_state.soc->save_cpu_target(&mbus_state, store_addr);
पूर्ण

अटल स्थिर काष्ठा mvebu_mbus_soc_data armada_370_mbus_data = अणु
	.num_wins            = 20,
	.has_mbus_bridge     = true,
	.win_cfg_offset      = armada_370_xp_mbus_win_cfg_offset,
	.win_remap_offset    = generic_mbus_win_remap_8_offset,
	.setup_cpu_target    = mvebu_mbus_शेष_setup_cpu_target,
	.show_cpu_target     = mvebu_sdram_debug_show_orion,
	.save_cpu_target     = mvebu_mbus_शेष_save_cpu_target,
पूर्ण;

अटल स्थिर काष्ठा mvebu_mbus_soc_data armada_xp_mbus_data = अणु
	.num_wins            = 20,
	.has_mbus_bridge     = true,
	.win_cfg_offset      = armada_370_xp_mbus_win_cfg_offset,
	.win_remap_offset    = armada_xp_mbus_win_remap_offset,
	.setup_cpu_target    = mvebu_mbus_शेष_setup_cpu_target,
	.show_cpu_target     = mvebu_sdram_debug_show_orion,
	.save_cpu_target     = mvebu_mbus_शेष_save_cpu_target,
पूर्ण;

अटल स्थिर काष्ठा mvebu_mbus_soc_data kirkwood_mbus_data = अणु
	.num_wins            = 8,
	.win_cfg_offset      = generic_mbus_win_cfg_offset,
	.save_cpu_target     = mvebu_mbus_शेष_save_cpu_target,
	.win_remap_offset    = generic_mbus_win_remap_4_offset,
	.setup_cpu_target    = mvebu_mbus_शेष_setup_cpu_target,
	.show_cpu_target     = mvebu_sdram_debug_show_orion,
पूर्ण;

अटल स्थिर काष्ठा mvebu_mbus_soc_data करोve_mbus_data = अणु
	.num_wins            = 8,
	.win_cfg_offset      = generic_mbus_win_cfg_offset,
	.save_cpu_target     = mvebu_mbus_करोve_save_cpu_target,
	.win_remap_offset    = generic_mbus_win_remap_4_offset,
	.setup_cpu_target    = mvebu_mbus_करोve_setup_cpu_target,
	.show_cpu_target     = mvebu_sdram_debug_show_करोve,
पूर्ण;

/*
 * Some variants of Orion5x have 4 remappable winकरोws, some other have
 * only two of them.
 */
अटल स्थिर काष्ठा mvebu_mbus_soc_data orion5x_4win_mbus_data = अणु
	.num_wins            = 8,
	.win_cfg_offset      = generic_mbus_win_cfg_offset,
	.save_cpu_target     = mvebu_mbus_शेष_save_cpu_target,
	.win_remap_offset    = generic_mbus_win_remap_4_offset,
	.setup_cpu_target    = mvebu_mbus_शेष_setup_cpu_target,
	.show_cpu_target     = mvebu_sdram_debug_show_orion,
पूर्ण;

अटल स्थिर काष्ठा mvebu_mbus_soc_data orion5x_2win_mbus_data = अणु
	.num_wins            = 8,
	.win_cfg_offset      = generic_mbus_win_cfg_offset,
	.save_cpu_target     = mvebu_mbus_शेष_save_cpu_target,
	.win_remap_offset    = generic_mbus_win_remap_2_offset,
	.setup_cpu_target    = mvebu_mbus_शेष_setup_cpu_target,
	.show_cpu_target     = mvebu_sdram_debug_show_orion,
पूर्ण;

अटल स्थिर काष्ठा mvebu_mbus_soc_data mv78xx0_mbus_data = अणु
	.num_wins            = 14,
	.win_cfg_offset      = mv78xx0_mbus_win_cfg_offset,
	.save_cpu_target     = mvebu_mbus_शेष_save_cpu_target,
	.win_remap_offset    = generic_mbus_win_remap_8_offset,
	.setup_cpu_target    = mvebu_mbus_शेष_setup_cpu_target,
	.show_cpu_target     = mvebu_sdram_debug_show_orion,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_mvebu_mbus_ids[] = अणु
	अणु .compatible = "marvell,armada370-mbus",
	  .data = &armada_370_mbus_data, पूर्ण,
	अणु .compatible = "marvell,armada375-mbus",
	  .data = &armada_xp_mbus_data, पूर्ण,
	अणु .compatible = "marvell,armada380-mbus",
	  .data = &armada_xp_mbus_data, पूर्ण,
	अणु .compatible = "marvell,armadaxp-mbus",
	  .data = &armada_xp_mbus_data, पूर्ण,
	अणु .compatible = "marvell,kirkwood-mbus",
	  .data = &kirkwood_mbus_data, पूर्ण,
	अणु .compatible = "marvell,dove-mbus",
	  .data = &करोve_mbus_data, पूर्ण,
	अणु .compatible = "marvell,orion5x-88f5281-mbus",
	  .data = &orion5x_4win_mbus_data, पूर्ण,
	अणु .compatible = "marvell,orion5x-88f5182-mbus",
	  .data = &orion5x_2win_mbus_data, पूर्ण,
	अणु .compatible = "marvell,orion5x-88f5181-mbus",
	  .data = &orion5x_2win_mbus_data, पूर्ण,
	अणु .compatible = "marvell,orion5x-88f6183-mbus",
	  .data = &orion5x_4win_mbus_data, पूर्ण,
	अणु .compatible = "marvell,mv78xx0-mbus",
	  .data = &mv78xx0_mbus_data, पूर्ण,
	अणु पूर्ण,
पूर्ण;

/*
 * Public API of the driver
 */
पूर्णांक mvebu_mbus_add_winकरोw_remap_by_id(अचिन्हित पूर्णांक target,
				      अचिन्हित पूर्णांक attribute,
				      phys_addr_t base, माप_प्रकार size,
				      phys_addr_t remap)
अणु
	काष्ठा mvebu_mbus_state *s = &mbus_state;

	अगर (!mvebu_mbus_winकरोw_conflicts(s, base, size, target, attribute)) अणु
		pr_err("cannot add window '%x:%x', conflicts with another window\n",
		       target, attribute);
		वापस -EINVAL;
	पूर्ण

	वापस mvebu_mbus_alloc_winकरोw(s, base, size, remap, target, attribute);
पूर्ण

पूर्णांक mvebu_mbus_add_winकरोw_by_id(अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक attribute,
				phys_addr_t base, माप_प्रकार size)
अणु
	वापस mvebu_mbus_add_winकरोw_remap_by_id(target, attribute, base,
						 size, MVEBU_MBUS_NO_REMAP);
पूर्ण

पूर्णांक mvebu_mbus_del_winकरोw(phys_addr_t base, माप_प्रकार size)
अणु
	पूर्णांक win;

	win = mvebu_mbus_find_winकरोw(&mbus_state, base, size);
	अगर (win < 0)
		वापस win;

	mvebu_mbus_disable_winकरोw(&mbus_state, win);
	वापस 0;
पूर्ण

व्योम mvebu_mbus_get_pcie_mem_aperture(काष्ठा resource *res)
अणु
	अगर (!res)
		वापस;
	*res = mbus_state.pcie_mem_aperture;
पूर्ण

व्योम mvebu_mbus_get_pcie_io_aperture(काष्ठा resource *res)
अणु
	अगर (!res)
		वापस;
	*res = mbus_state.pcie_io_aperture;
पूर्ण

पूर्णांक mvebu_mbus_get_dram_win_info(phys_addr_t phyaddr, u8 *target, u8 *attr)
अणु
	स्थिर काष्ठा mbus_dram_target_info *dram;
	पूर्णांक i;

	/* Get dram info */
	dram = mv_mbus_dram_info();
	अगर (!dram) अणु
		pr_err("missing DRAM information\n");
		वापस -ENODEV;
	पूर्ण

	/* Try to find matching DRAM winकरोw क्रम phyaddr */
	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		अगर (cs->base <= phyaddr &&
			phyaddr <= (cs->base + cs->size - 1)) अणु
			*target = dram->mbus_dram_target_id;
			*attr = cs->mbus_attr;
			वापस 0;
		पूर्ण
	पूर्ण

	pr_err("invalid dram address %pa\n", &phyaddr);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(mvebu_mbus_get_dram_win_info);

पूर्णांक mvebu_mbus_get_io_win_info(phys_addr_t phyaddr, u32 *size, u8 *target,
			       u8 *attr)
अणु
	पूर्णांक win;

	क्रम (win = 0; win < mbus_state.soc->num_wins; win++) अणु
		u64 wbase;
		पूर्णांक enabled;

		mvebu_mbus_पढ़ो_winकरोw(&mbus_state, win, &enabled, &wbase,
				       size, target, attr, शून्य);

		अगर (!enabled)
			जारी;

		अगर (wbase <= phyaddr && phyaddr <= wbase + *size)
			वापस win;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(mvebu_mbus_get_io_win_info);

अटल __init पूर्णांक mvebu_mbus_debugfs_init(व्योम)
अणु
	काष्ठा mvebu_mbus_state *s = &mbus_state;

	/*
	 * If no base has been initialized, करोesn't make sense to
	 * रेजिस्टर the debugfs entries. We may be on a multiplatक्रमm
	 * kernel that isn't running a Marvell EBU SoC.
	 */
	अगर (!s->mbuswins_base)
		वापस 0;

	s->debugfs_root = debugfs_create_dir("mvebu-mbus", शून्य);
	अगर (s->debugfs_root) अणु
		s->debugfs_sdram = debugfs_create_file("sdram", S_IRUGO,
						       s->debugfs_root, शून्य,
						       &mvebu_sdram_debug_fops);
		s->debugfs_devs = debugfs_create_file("devices", S_IRUGO,
						      s->debugfs_root, शून्य,
						      &mvebu_devs_debug_fops);
	पूर्ण

	वापस 0;
पूर्ण
fs_initcall(mvebu_mbus_debugfs_init);

अटल पूर्णांक mvebu_mbus_suspend(व्योम)
अणु
	काष्ठा mvebu_mbus_state *s = &mbus_state;
	पूर्णांक win;

	अगर (!s->mbusbridge_base)
		वापस -ENODEV;

	क्रम (win = 0; win < s->soc->num_wins; win++) अणु
		व्योम __iomem *addr = s->mbuswins_base +
			s->soc->win_cfg_offset(win);
		व्योम __iomem *addr_rmp;

		s->wins[win].base = पढ़ोl(addr + WIN_BASE_OFF);
		s->wins[win].ctrl = पढ़ोl(addr + WIN_CTRL_OFF);

		अगर (!mvebu_mbus_winकरोw_is_remappable(s, win))
			जारी;

		addr_rmp = s->mbuswins_base +
			s->soc->win_remap_offset(win);

		s->wins[win].remap_lo = पढ़ोl(addr_rmp + WIN_REMAP_LO_OFF);
		s->wins[win].remap_hi = पढ़ोl(addr_rmp + WIN_REMAP_HI_OFF);
	पूर्ण

	s->mbus_bridge_ctrl = पढ़ोl(s->mbusbridge_base +
				    MBUS_BRIDGE_CTRL_OFF);
	s->mbus_bridge_base = पढ़ोl(s->mbusbridge_base +
				    MBUS_BRIDGE_BASE_OFF);

	वापस 0;
पूर्ण

अटल व्योम mvebu_mbus_resume(व्योम)
अणु
	काष्ठा mvebu_mbus_state *s = &mbus_state;
	पूर्णांक win;

	ग_लिखोl(s->mbus_bridge_ctrl,
	       s->mbusbridge_base + MBUS_BRIDGE_CTRL_OFF);
	ग_लिखोl(s->mbus_bridge_base,
	       s->mbusbridge_base + MBUS_BRIDGE_BASE_OFF);

	क्रम (win = 0; win < s->soc->num_wins; win++) अणु
		व्योम __iomem *addr = s->mbuswins_base +
			s->soc->win_cfg_offset(win);
		व्योम __iomem *addr_rmp;

		ग_लिखोl(s->wins[win].base, addr + WIN_BASE_OFF);
		ग_लिखोl(s->wins[win].ctrl, addr + WIN_CTRL_OFF);

		अगर (!mvebu_mbus_winकरोw_is_remappable(s, win))
			जारी;

		addr_rmp = s->mbuswins_base +
			s->soc->win_remap_offset(win);

		ग_लिखोl(s->wins[win].remap_lo, addr_rmp + WIN_REMAP_LO_OFF);
		ग_लिखोl(s->wins[win].remap_hi, addr_rmp + WIN_REMAP_HI_OFF);
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops mvebu_mbus_syscore_ops = अणु
	.suspend	= mvebu_mbus_suspend,
	.resume		= mvebu_mbus_resume,
पूर्ण;

अटल पूर्णांक __init mvebu_mbus_common_init(काष्ठा mvebu_mbus_state *mbus,
					 phys_addr_t mbuswins_phys_base,
					 माप_प्रकार mbuswins_size,
					 phys_addr_t sdramwins_phys_base,
					 माप_प्रकार sdramwins_size,
					 phys_addr_t mbusbridge_phys_base,
					 माप_प्रकार mbusbridge_size,
					 bool is_coherent)
अणु
	पूर्णांक win;

	mbus->mbuswins_base = ioremap(mbuswins_phys_base, mbuswins_size);
	अगर (!mbus->mbuswins_base)
		वापस -ENOMEM;

	mbus->sdramwins_base = ioremap(sdramwins_phys_base, sdramwins_size);
	अगर (!mbus->sdramwins_base) अणु
		iounmap(mbus->mbuswins_base);
		वापस -ENOMEM;
	पूर्ण

	mbus->sdramwins_phys_base = sdramwins_phys_base;

	अगर (mbusbridge_phys_base) अणु
		mbus->mbusbridge_base = ioremap(mbusbridge_phys_base,
						mbusbridge_size);
		अगर (!mbus->mbusbridge_base) अणु
			iounmap(mbus->sdramwins_base);
			iounmap(mbus->mbuswins_base);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा
		mbus->mbusbridge_base = शून्य;

	क्रम (win = 0; win < mbus->soc->num_wins; win++)
		mvebu_mbus_disable_winकरोw(mbus, win);

	mbus->soc->setup_cpu_target(mbus);
	mvebu_mbus_setup_cpu_target_nooverlap(mbus);

	अगर (is_coherent)
		ग_लिखोl(UNIT_SYNC_BARRIER_ALL,
		       mbus->mbuswins_base + UNIT_SYNC_BARRIER_OFF);

	रेजिस्टर_syscore_ops(&mvebu_mbus_syscore_ops);

	वापस 0;
पूर्ण

पूर्णांक __init mvebu_mbus_init(स्थिर अक्षर *soc, phys_addr_t mbuswins_phys_base,
			   माप_प्रकार mbuswins_size,
			   phys_addr_t sdramwins_phys_base,
			   माप_प्रकार sdramwins_size)
अणु
	स्थिर काष्ठा of_device_id *of_id;

	क्रम (of_id = of_mvebu_mbus_ids; of_id->compatible[0]; of_id++)
		अगर (!म_भेद(of_id->compatible, soc))
			अवरोध;

	अगर (!of_id->compatible[0]) अणु
		pr_err("could not find a matching SoC family\n");
		वापस -ENODEV;
	पूर्ण

	mbus_state.soc = of_id->data;

	वापस mvebu_mbus_common_init(&mbus_state,
			mbuswins_phys_base,
			mbuswins_size,
			sdramwins_phys_base,
			sdramwins_size, 0, 0, false);
पूर्ण

#अगर_घोषित CONFIG_OF
/*
 * The winकरोw IDs in the ranges DT property have the following क्रमmat:
 *  - bits 28 to 31: MBus custom field
 *  - bits 24 to 27: winकरोw target ID
 *  - bits 16 to 23: winकरोw attribute ID
 *  - bits  0 to 15: unused
 */
#घोषणा CUSTOM(id) (((id) & 0xF0000000) >> 24)
#घोषणा TARGET(id) (((id) & 0x0F000000) >> 24)
#घोषणा ATTR(id)   (((id) & 0x00FF0000) >> 16)

अटल पूर्णांक __init mbus_dt_setup_win(काष्ठा mvebu_mbus_state *mbus,
				    u32 base, u32 size,
				    u8 target, u8 attr)
अणु
	अगर (!mvebu_mbus_winकरोw_conflicts(mbus, base, size, target, attr)) अणु
		pr_err("cannot add window '%04x:%04x', conflicts with another window\n",
		       target, attr);
		वापस -EBUSY;
	पूर्ण

	अगर (mvebu_mbus_alloc_winकरोw(mbus, base, size, MVEBU_MBUS_NO_REMAP,
				    target, attr)) अणु
		pr_err("cannot add window '%04x:%04x', too many windows\n",
		       target, attr);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init
mbus_parse_ranges(काष्ठा device_node *node,
		  पूर्णांक *addr_cells, पूर्णांक *c_addr_cells, पूर्णांक *c_size_cells,
		  पूर्णांक *cell_count, स्थिर __be32 **ranges_start,
		  स्थिर __be32 **ranges_end)
अणु
	स्थिर __be32 *prop;
	पूर्णांक ranges_len, tuple_len;

	/* Allow a node with no 'ranges' property */
	*ranges_start = of_get_property(node, "ranges", &ranges_len);
	अगर (*ranges_start == शून्य) अणु
		*addr_cells = *c_addr_cells = *c_size_cells = *cell_count = 0;
		*ranges_start = *ranges_end = शून्य;
		वापस 0;
	पूर्ण
	*ranges_end = *ranges_start + ranges_len / माप(__be32);

	*addr_cells = of_n_addr_cells(node);

	prop = of_get_property(node, "#address-cells", शून्य);
	*c_addr_cells = be32_to_cpup(prop);

	prop = of_get_property(node, "#size-cells", शून्य);
	*c_size_cells = be32_to_cpup(prop);

	*cell_count = *addr_cells + *c_addr_cells + *c_size_cells;
	tuple_len = (*cell_count) * माप(__be32);

	अगर (ranges_len % tuple_len) अणु
		pr_warn("malformed ranges entry '%pOFn'\n", node);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init mbus_dt_setup(काष्ठा mvebu_mbus_state *mbus,
				काष्ठा device_node *np)
अणु
	पूर्णांक addr_cells, c_addr_cells, c_size_cells;
	पूर्णांक i, ret, cell_count;
	स्थिर __be32 *r, *ranges_start, *ranges_end;

	ret = mbus_parse_ranges(np, &addr_cells, &c_addr_cells,
				&c_size_cells, &cell_count,
				&ranges_start, &ranges_end);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0, r = ranges_start; r < ranges_end; r += cell_count, i++) अणु
		u32 winकरोwid, base, size;
		u8 target, attr;

		/*
		 * An entry with a non-zero custom field करो not
		 * correspond to a अटल winकरोw, so skip it.
		 */
		winकरोwid = of_पढ़ो_number(r, 1);
		अगर (CUSTOM(winकरोwid))
			जारी;

		target = TARGET(winकरोwid);
		attr = ATTR(winकरोwid);

		base = of_पढ़ो_number(r + c_addr_cells, addr_cells);
		size = of_पढ़ो_number(r + c_addr_cells + addr_cells,
				      c_size_cells);
		ret = mbus_dt_setup_win(mbus, base, size, target, attr);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init mvebu_mbus_get_pcie_resources(काष्ठा device_node *np,
						 काष्ठा resource *mem,
						 काष्ठा resource *io)
अणु
	u32 reg[2];
	पूर्णांक ret;

	/*
	 * These are optional, so we make sure that resource_size(x) will
	 * वापस 0.
	 */
	स_रखो(mem, 0, माप(काष्ठा resource));
	mem->end = -1;
	स_रखो(io, 0, माप(काष्ठा resource));
	io->end = -1;

	ret = of_property_पढ़ो_u32_array(np, "pcie-mem-aperture", reg, ARRAY_SIZE(reg));
	अगर (!ret) अणु
		mem->start = reg[0];
		mem->end = mem->start + reg[1] - 1;
		mem->flags = IORESOURCE_MEM;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(np, "pcie-io-aperture", reg, ARRAY_SIZE(reg));
	अगर (!ret) अणु
		io->start = reg[0];
		io->end = io->start + reg[1] - 1;
		io->flags = IORESOURCE_IO;
	पूर्ण
पूर्ण

पूर्णांक __init mvebu_mbus_dt_init(bool is_coherent)
अणु
	काष्ठा resource mbuswins_res, sdramwins_res, mbusbridge_res;
	काष्ठा device_node *np, *controller;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर __be32 *prop;
	पूर्णांक ret;

	np = of_find_matching_node_and_match(शून्य, of_mvebu_mbus_ids, &of_id);
	अगर (!np) अणु
		pr_err("could not find a matching SoC family\n");
		वापस -ENODEV;
	पूर्ण

	mbus_state.soc = of_id->data;

	prop = of_get_property(np, "controller", शून्य);
	अगर (!prop) अणु
		pr_err("required 'controller' property missing\n");
		वापस -EINVAL;
	पूर्ण

	controller = of_find_node_by_phandle(be32_to_cpup(prop));
	अगर (!controller) अणु
		pr_err("could not find an 'mbus-controller' node\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_address_to_resource(controller, 0, &mbuswins_res)) अणु
		pr_err("cannot get MBUS register address\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_address_to_resource(controller, 1, &sdramwins_res)) अणु
		pr_err("cannot get SDRAM register address\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set the resource to 0 so that it can be left unmapped by
	 * mvebu_mbus_common_init() अगर the DT करोesn't carry the
	 * necessary inक्रमmation. This is needed to preserve backward
	 * compatibility.
	 */
	स_रखो(&mbusbridge_res, 0, माप(mbusbridge_res));

	अगर (mbus_state.soc->has_mbus_bridge) अणु
		अगर (of_address_to_resource(controller, 2, &mbusbridge_res))
			pr_warn(FW_WARN "deprecated mbus-mvebu Device Tree, suspend/resume will not work\n");
	पूर्ण

	mbus_state.hw_io_coherency = is_coherent;

	/* Get optional pcie-अणुmem,ioपूर्ण-aperture properties */
	mvebu_mbus_get_pcie_resources(np, &mbus_state.pcie_mem_aperture,
					  &mbus_state.pcie_io_aperture);

	ret = mvebu_mbus_common_init(&mbus_state,
				     mbuswins_res.start,
				     resource_size(&mbuswins_res),
				     sdramwins_res.start,
				     resource_size(&sdramwins_res),
				     mbusbridge_res.start,
				     resource_size(&mbusbridge_res),
				     is_coherent);
	अगर (ret)
		वापस ret;

	/* Setup अटलally declared winकरोws in the DT */
	वापस mbus_dt_setup(&mbus_state, np);
पूर्ण
#पूर्ण_अगर
