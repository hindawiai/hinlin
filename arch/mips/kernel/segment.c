<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2013 Imagination Technologies Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/mipsregs.h>

अटल व्योम build_segment_config(अक्षर *str, अचिन्हित पूर्णांक cfg)
अणु
	अचिन्हित पूर्णांक am;
	अटल स्थिर अक्षर * स्थिर am_str[] = अणु
		"UK", "MK", "MSK", "MUSK", "MUSUK", "USK",
		"RSRVD", "UUSK"पूर्ण;

	/* Segment access mode. */
	am = (cfg & MIPS_SEGCFG_AM) >> MIPS_SEGCFG_AM_SHIFT;
	str += प्र_लिखो(str, "%-5s", am_str[am]);

	/*
	 * Access modes MK, MSK and MUSK are mapped segments. Thereक्रमe
	 * there is no direct physical address mapping unless it becomes
	 * unmapped uncached at error level due to EU.
	 */
	अगर ((am == 0) || (am > 3) || (cfg & MIPS_SEGCFG_EU))
		str += प्र_लिखो(str, "         %03lx",
			((cfg & MIPS_SEGCFG_PA) >> MIPS_SEGCFG_PA_SHIFT));
	अन्यथा
		str += प्र_लिखो(str, "         UND");

	अगर ((am == 0) || (am > 3))
		str += प्र_लिखो(str, "         %01ld",
			((cfg & MIPS_SEGCFG_C) >> MIPS_SEGCFG_C_SHIFT));
	अन्यथा
		str += प्र_लिखो(str, "         U");

	/* Exception configuration. */
	str += प्र_लिखो(str, "       %01ld\n",
		((cfg & MIPS_SEGCFG_EU) >> MIPS_SEGCFG_EU_SHIFT));
पूर्ण

अटल पूर्णांक show_segments(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित पूर्णांक segcfg;
	अक्षर str[42];

	seq_माला_दो(m, "Segment   Virtual    Size   Access Mode   Physical   Caching   EU\n");
	seq_माला_दो(m, "-------   -------    ----   -----------   --------   -------   --\n");

	segcfg = पढ़ो_c0_segctl0();
	build_segment_config(str, segcfg);
	seq_म_लिखो(m, "   0      e0000000   512M      %s", str);

	segcfg >>= 16;
	build_segment_config(str, segcfg);
	seq_म_लिखो(m, "   1      c0000000   512M      %s", str);

	segcfg = पढ़ो_c0_segctl1();
	build_segment_config(str, segcfg);
	seq_म_लिखो(m, "   2      a0000000   512M      %s", str);

	segcfg >>= 16;
	build_segment_config(str, segcfg);
	seq_म_लिखो(m, "   3      80000000   512M      %s", str);

	segcfg = पढ़ो_c0_segctl2();
	build_segment_config(str, segcfg);
	seq_म_लिखो(m, "   4      40000000    1G       %s", str);

	segcfg >>= 16;
	build_segment_config(str, segcfg);
	seq_म_लिखो(m, "   5      00000000    1G       %s\n", str);

	वापस 0;
पूर्ण

अटल पूर्णांक segments_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, show_segments, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations segments_fops = अणु
	.खोलो		= segments_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक __init segments_info(व्योम)
अणु
	अगर (cpu_has_segments)
		debugfs_create_file("segments", S_IRUGO, mips_debugfs_dir, शून्य,
				    &segments_fops);
	वापस 0;
पूर्ण

device_initcall(segments_info);
