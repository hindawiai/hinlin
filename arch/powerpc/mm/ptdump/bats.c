<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018, Christophe Leroy CS S.I.
 * <christophe.leroy@c-s.fr>
 *
 * This dumps the content of BATS
 */

#समावेश <linux/pgtable.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/cpu_has_feature.h>

#समावेश "ptdump.h"

अटल व्योम bat_show_603(काष्ठा seq_file *m, पूर्णांक idx, u32 lower, u32 upper, bool is_d)
अणु
	u32 bepi = upper & 0xfffe0000;
	u32 bl = (upper >> 2) & 0x7ff;
	u32 k = upper & 3;
	phys_addr_t brpn = PHYS_BAT_ADDR(lower);
	u32 size = (bl + 1) << 17;

	seq_म_लिखो(m, "%d: ", idx);
	अगर (k == 0) अणु
		seq_माला_दो(m, "        -\n");
		वापस;
	पूर्ण

	seq_म_लिखो(m, "0x%08x-0x%08x ", bepi, bepi + size - 1);
#अगर_घोषित CONFIG_PHYS_64BIT
	seq_म_लिखो(m, "0x%016llx ", brpn);
#अन्यथा
	seq_म_लिखो(m, "0x%08x ", brpn);
#पूर्ण_अगर
	pt_dump_size(m, size);

	अगर (k == 1)
		seq_माला_दो(m, "User ");
	अन्यथा अगर (k == 2)
		seq_माला_दो(m, "Kernel ");
	अन्यथा
		seq_माला_दो(m, "Kernel/User ");

	अगर (lower & BPP_RX)
		seq_माला_दो(m, is_d ? "r   " : "  x ");
	अन्यथा अगर (lower & BPP_RW)
		seq_माला_दो(m, is_d ? "rw  " : "  x ");
	अन्यथा
		seq_माला_दो(m, is_d ? "    " : "    ");

	seq_माला_दो(m, lower & _PAGE_WRITETHRU ? "w " : "  ");
	seq_माला_दो(m, lower & _PAGE_NO_CACHE ? "i " : "  ");
	seq_माला_दो(m, lower & _PAGE_COHERENT ? "m " : "  ");
	seq_माला_दो(m, lower & _PAGE_GUARDED ? "g " : "  ");
	seq_माला_दो(m, "\n");
पूर्ण

#घोषणा BAT_SHOW_603(_m, _n, _l, _u, _d) bat_show_603(_m, _n, mfspr(_l), mfspr(_u), _d)

अटल पूर्णांक bats_show_603(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_माला_दो(m, "---[ Instruction Block Address Translation ]---\n");

	BAT_SHOW_603(m, 0, SPRN_IBAT0L, SPRN_IBAT0U, false);
	BAT_SHOW_603(m, 1, SPRN_IBAT1L, SPRN_IBAT1U, false);
	BAT_SHOW_603(m, 2, SPRN_IBAT2L, SPRN_IBAT2U, false);
	BAT_SHOW_603(m, 3, SPRN_IBAT3L, SPRN_IBAT3U, false);
	अगर (mmu_has_feature(MMU_FTR_USE_HIGH_BATS)) अणु
		BAT_SHOW_603(m, 4, SPRN_IBAT4L, SPRN_IBAT4U, false);
		BAT_SHOW_603(m, 5, SPRN_IBAT5L, SPRN_IBAT5U, false);
		BAT_SHOW_603(m, 6, SPRN_IBAT6L, SPRN_IBAT6U, false);
		BAT_SHOW_603(m, 7, SPRN_IBAT7L, SPRN_IBAT7U, false);
	पूर्ण

	seq_माला_दो(m, "\n---[ Data Block Address Translation ]---\n");

	BAT_SHOW_603(m, 0, SPRN_DBAT0L, SPRN_DBAT0U, true);
	BAT_SHOW_603(m, 1, SPRN_DBAT1L, SPRN_DBAT1U, true);
	BAT_SHOW_603(m, 2, SPRN_DBAT2L, SPRN_DBAT2U, true);
	BAT_SHOW_603(m, 3, SPRN_DBAT3L, SPRN_DBAT3U, true);
	अगर (mmu_has_feature(MMU_FTR_USE_HIGH_BATS)) अणु
		BAT_SHOW_603(m, 4, SPRN_DBAT4L, SPRN_DBAT4U, true);
		BAT_SHOW_603(m, 5, SPRN_DBAT5L, SPRN_DBAT5U, true);
		BAT_SHOW_603(m, 6, SPRN_DBAT6L, SPRN_DBAT6U, true);
		BAT_SHOW_603(m, 7, SPRN_DBAT7L, SPRN_DBAT7U, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, bats_show_603, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations bats_fops = अणु
	.खोलो		= bats_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक __init bats_init(व्योम)
अणु
	debugfs_create_file("block_address_translation", 0400,
			    घातerpc_debugfs_root, शून्य, &bats_fops);
	वापस 0;
पूर्ण
device_initcall(bats_init);
