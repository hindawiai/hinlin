<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cbe_regs.c
 *
 * Accessor routines क्रम the various MMIO रेजिस्टर blocks of the CBE
 *
 * (c) 2006 Benjamin Herrenschmidt <benh@kernel.crashing.org>, IBM Corp.
 */

#समावेश <linux/percpu.h>
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/cell-regs.h>

/*
 * Current implementation uses "cpu" nodes. We build our own mapping
 * array of cpu numbers to cpu nodes locally क्रम now to allow पूर्णांकerrupt
 * समय code to have a fast path rather than call of_get_cpu_node(). If
 * we implement cpu hotplug, we'll have to install an appropriate norअगरier
 * in order to release references to the cpu going away
 */
अटल काष्ठा cbe_regs_map
अणु
	काष्ठा device_node *cpu_node;
	काष्ठा device_node *be_node;
	काष्ठा cbe_pmd_regs __iomem *pmd_regs;
	काष्ठा cbe_iic_regs __iomem *iic_regs;
	काष्ठा cbe_mic_पंचांग_regs __iomem *mic_पंचांग_regs;
	काष्ठा cbe_pmd_shaकरोw_regs pmd_shaकरोw_regs;
पूर्ण cbe_regs_maps[MAX_CBE];
अटल पूर्णांक cbe_regs_map_count;

अटल काष्ठा cbe_thपढ़ो_map
अणु
	काष्ठा device_node *cpu_node;
	काष्ठा device_node *be_node;
	काष्ठा cbe_regs_map *regs;
	अचिन्हित पूर्णांक thपढ़ो_id;
	अचिन्हित पूर्णांक cbe_id;
पूर्ण cbe_thपढ़ो_map[NR_CPUS];

अटल cpumask_t cbe_local_mask[MAX_CBE] = अणु [0 ... MAX_CBE-1] = अणुCPU_BITS_NONEपूर्ण पूर्ण;
अटल cpumask_t cbe_first_online_cpu = अणु CPU_BITS_NONE पूर्ण;

अटल काष्ठा cbe_regs_map *cbe_find_map(काष्ठा device_node *np)
अणु
	पूर्णांक i;
	काष्ठा device_node *पंचांगp_np;

	अगर (!of_node_is_type(np, "spe")) अणु
		क्रम (i = 0; i < cbe_regs_map_count; i++)
			अगर (cbe_regs_maps[i].cpu_node == np ||
			    cbe_regs_maps[i].be_node == np)
				वापस &cbe_regs_maps[i];
		वापस शून्य;
	पूर्ण

	अगर (np->data)
		वापस np->data;

	/* walk up path until cpu or be node was found */
	पंचांगp_np = np;
	करो अणु
		पंचांगp_np = पंचांगp_np->parent;
		/* on a correct devicetree we wont get up to root */
		BUG_ON(!पंचांगp_np);
	पूर्ण जबतक (!of_node_is_type(पंचांगp_np, "cpu") ||
		 !of_node_is_type(पंचांगp_np, "be"));

	np->data = cbe_find_map(पंचांगp_np);

	वापस np->data;
पूर्ण

काष्ठा cbe_pmd_regs __iomem *cbe_get_pmd_regs(काष्ठा device_node *np)
अणु
	काष्ठा cbe_regs_map *map = cbe_find_map(np);
	अगर (map == शून्य)
		वापस शून्य;
	वापस map->pmd_regs;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_get_pmd_regs);

काष्ठा cbe_pmd_regs __iomem *cbe_get_cpu_pmd_regs(पूर्णांक cpu)
अणु
	काष्ठा cbe_regs_map *map = cbe_thपढ़ो_map[cpu].regs;
	अगर (map == शून्य)
		वापस शून्य;
	वापस map->pmd_regs;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_get_cpu_pmd_regs);

काष्ठा cbe_pmd_shaकरोw_regs *cbe_get_pmd_shaकरोw_regs(काष्ठा device_node *np)
अणु
	काष्ठा cbe_regs_map *map = cbe_find_map(np);
	अगर (map == शून्य)
		वापस शून्य;
	वापस &map->pmd_shaकरोw_regs;
पूर्ण

काष्ठा cbe_pmd_shaकरोw_regs *cbe_get_cpu_pmd_shaकरोw_regs(पूर्णांक cpu)
अणु
	काष्ठा cbe_regs_map *map = cbe_thपढ़ो_map[cpu].regs;
	अगर (map == शून्य)
		वापस शून्य;
	वापस &map->pmd_shaकरोw_regs;
पूर्ण

काष्ठा cbe_iic_regs __iomem *cbe_get_iic_regs(काष्ठा device_node *np)
अणु
	काष्ठा cbe_regs_map *map = cbe_find_map(np);
	अगर (map == शून्य)
		वापस शून्य;
	वापस map->iic_regs;
पूर्ण

काष्ठा cbe_iic_regs __iomem *cbe_get_cpu_iic_regs(पूर्णांक cpu)
अणु
	काष्ठा cbe_regs_map *map = cbe_thपढ़ो_map[cpu].regs;
	अगर (map == शून्य)
		वापस शून्य;
	वापस map->iic_regs;
पूर्ण

काष्ठा cbe_mic_पंचांग_regs __iomem *cbe_get_mic_पंचांग_regs(काष्ठा device_node *np)
अणु
	काष्ठा cbe_regs_map *map = cbe_find_map(np);
	अगर (map == शून्य)
		वापस शून्य;
	वापस map->mic_पंचांग_regs;
पूर्ण

काष्ठा cbe_mic_पंचांग_regs __iomem *cbe_get_cpu_mic_पंचांग_regs(पूर्णांक cpu)
अणु
	काष्ठा cbe_regs_map *map = cbe_thपढ़ो_map[cpu].regs;
	अगर (map == शून्य)
		वापस शून्य;
	वापस map->mic_पंचांग_regs;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_get_cpu_mic_पंचांग_regs);

u32 cbe_get_hw_thपढ़ो_id(पूर्णांक cpu)
अणु
	वापस cbe_thपढ़ो_map[cpu].thपढ़ो_id;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_get_hw_thपढ़ो_id);

u32 cbe_cpu_to_node(पूर्णांक cpu)
अणु
	वापस cbe_thपढ़ो_map[cpu].cbe_id;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_cpu_to_node);

u32 cbe_node_to_cpu(पूर्णांक node)
अणु
	वापस cpumask_first(&cbe_local_mask[node]);

पूर्ण
EXPORT_SYMBOL_GPL(cbe_node_to_cpu);

अटल काष्ठा device_node *cbe_get_be_node(पूर्णांक cpu_id)
अणु
	काष्ठा device_node *np;

	क्रम_each_node_by_type (np, "be") अणु
		पूर्णांक len,i;
		स्थिर phandle *cpu_handle;

		cpu_handle = of_get_property(np, "cpus", &len);

		/*
		 * the CAB SLOF tree is non compliant, so we just assume
		 * there is only one node
		 */
		अगर (WARN_ON_ONCE(!cpu_handle))
			वापस np;

		क्रम (i=0; i<len; i++)
			अगर (of_find_node_by_phandle(cpu_handle[i]) == of_get_cpu_node(cpu_id, शून्य))
				वापस np;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __init cbe_fill_regs_map(काष्ठा cbe_regs_map *map)
अणु
	अगर(map->be_node) अणु
		काष्ठा device_node *be, *np;

		be = map->be_node;

		क्रम_each_node_by_type(np, "pervasive")
			अगर (of_get_parent(np) == be)
				map->pmd_regs = of_iomap(np, 0);

		क्रम_each_node_by_type(np, "CBEA-Internal-Interrupt-Controller")
			अगर (of_get_parent(np) == be)
				map->iic_regs = of_iomap(np, 2);

		क्रम_each_node_by_type(np, "mic-tm")
			अगर (of_get_parent(np) == be)
				map->mic_पंचांग_regs = of_iomap(np, 0);
	पूर्ण अन्यथा अणु
		काष्ठा device_node *cpu;
		/* That hack must die die die ! */
		स्थिर काष्ठा address_prop अणु
			अचिन्हित दीर्घ address;
			अचिन्हित पूर्णांक len;
		पूर्ण __attribute__((packed)) *prop;

		cpu = map->cpu_node;

		prop = of_get_property(cpu, "pervasive", शून्य);
		अगर (prop != शून्य)
			map->pmd_regs = ioremap(prop->address, prop->len);

		prop = of_get_property(cpu, "iic", शून्य);
		अगर (prop != शून्य)
			map->iic_regs = ioremap(prop->address, prop->len);

		prop = of_get_property(cpu, "mic-tm", शून्य);
		अगर (prop != शून्य)
			map->mic_पंचांग_regs = ioremap(prop->address, prop->len);
	पूर्ण
पूर्ण


व्योम __init cbe_regs_init(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक thपढ़ो_id;
	काष्ठा device_node *cpu;

	/* Build local fast map of CPUs */
	क्रम_each_possible_cpu(i) अणु
		cbe_thपढ़ो_map[i].cpu_node = of_get_cpu_node(i, &thपढ़ो_id);
		cbe_thपढ़ो_map[i].be_node = cbe_get_be_node(i);
		cbe_thपढ़ो_map[i].thपढ़ो_id = thपढ़ो_id;
	पूर्ण

	/* Find maps क्रम each device tree CPU */
	क्रम_each_node_by_type(cpu, "cpu") अणु
		काष्ठा cbe_regs_map *map;
		अचिन्हित पूर्णांक cbe_id;

		cbe_id = cbe_regs_map_count++;
		map = &cbe_regs_maps[cbe_id];

		अगर (cbe_regs_map_count > MAX_CBE) अणु
			prपूर्णांकk(KERN_ERR "cbe_regs: More BE chips than supported"
			       "!\n");
			cbe_regs_map_count--;
			of_node_put(cpu);
			वापस;
		पूर्ण
		map->cpu_node = cpu;

		क्रम_each_possible_cpu(i) अणु
			काष्ठा cbe_thपढ़ो_map *thपढ़ो = &cbe_thपढ़ो_map[i];

			अगर (thपढ़ो->cpu_node == cpu) अणु
				thपढ़ो->regs = map;
				thपढ़ो->cbe_id = cbe_id;
				map->be_node = thपढ़ो->be_node;
				cpumask_set_cpu(i, &cbe_local_mask[cbe_id]);
				अगर(thपढ़ो->thपढ़ो_id == 0)
					cpumask_set_cpu(i, &cbe_first_online_cpu);
			पूर्ण
		पूर्ण

		cbe_fill_regs_map(map);
	पूर्ण
पूर्ण

