<शैली गुरु>
/*
 * debugfs ops क्रम the L1 cache
 *
 *  Copyright (C) 2006  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/पन.स>

क्रमागत cache_type अणु
	CACHE_TYPE_ICACHE,
	CACHE_TYPE_DCACHE,
	CACHE_TYPE_UNIFIED,
पूर्ण;

अटल पूर्णांक cache_debugfs_show(काष्ठा seq_file *file, व्योम *iter)
अणु
	अचिन्हित पूर्णांक cache_type = (अचिन्हित पूर्णांक)file->निजी;
	काष्ठा cache_info *cache;
	अचिन्हित पूर्णांक waysize, way;
	अचिन्हित दीर्घ ccr;
	अचिन्हित दीर्घ addrstart = 0;

	/*
	 * Go uncached immediately so we करोn't skew the results any
	 * more than we alपढ़ोy are..
	 */
	jump_to_uncached();

	ccr = __raw_पढ़ोl(SH_CCR);
	अगर ((ccr & CCR_CACHE_ENABLE) == 0) अणु
		back_to_cached();

		seq_म_लिखो(file, "disabled\n");
		वापस 0;
	पूर्ण

	अगर (cache_type == CACHE_TYPE_DCACHE) अणु
		addrstart = CACHE_OC_ADDRESS_ARRAY;
		cache = &current_cpu_data.dcache;
	पूर्ण अन्यथा अणु
		addrstart = CACHE_IC_ADDRESS_ARRAY;
		cache = &current_cpu_data.icache;
	पूर्ण

	waysize = cache->sets;

	/*
	 * If the OC is alपढ़ोy in RAM mode, we only have
	 * half of the entries to consider..
	 */
	अगर ((ccr & CCR_CACHE_ORA) && cache_type == CACHE_TYPE_DCACHE)
		waysize >>= 1;

	waysize <<= cache->entry_shअगरt;

	क्रम (way = 0; way < cache->ways; way++) अणु
		अचिन्हित दीर्घ addr;
		अचिन्हित पूर्णांक line;

		seq_म_लिखो(file, "-----------------------------------------\n");
		seq_म_लिखो(file, "Way %d\n", way);
		seq_म_लिखो(file, "-----------------------------------------\n");

		क्रम (addr = addrstart, line = 0;
		     addr < addrstart + waysize;
		     addr += cache->linesz, line++) अणु
			अचिन्हित दीर्घ data = __raw_पढ़ोl(addr);

			/* Check the V bit, ignore invalid cachelines */
			अगर ((data & 1) == 0)
				जारी;

			/* U: Dirty, cache tag is 10 bits up */
			seq_म_लिखो(file, "%3d: %c 0x%lx\n",
				   line, data & 2 ? 'U' : ' ',
				   data & 0x1ffffc00);
		पूर्ण

		addrstart += cache->way_incr;
	पूर्ण

	back_to_cached();

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(cache_debugfs);

अटल पूर्णांक __init cache_debugfs_init(व्योम)
अणु
	debugfs_create_file("dcache", S_IRUSR, arch_debugfs_dir,
			    (व्योम *)CACHE_TYPE_DCACHE, &cache_debugfs_fops);
	debugfs_create_file("icache", S_IRUSR, arch_debugfs_dir,
			    (व्योम *)CACHE_TYPE_ICACHE, &cache_debugfs_fops);
	वापस 0;
पूर्ण
module_init(cache_debugfs_init);

MODULE_LICENSE("GPL v2");
