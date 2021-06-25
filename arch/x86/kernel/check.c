<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/setup.h>

/*
 * Some BIOSes seem to corrupt the low 64k of memory during events
 * like suspend/resume and unplugging an HDMI cable.  Reserve all
 * reमुख्यing मुक्त memory in that area and fill it with a distinct
 * pattern.
 */
#घोषणा MAX_SCAN_AREAS	8

अटल पूर्णांक __पढ़ो_mostly memory_corruption_check = -1;

अटल अचिन्हित __पढ़ो_mostly corruption_check_size = 64*1024;
अटल अचिन्हित __पढ़ो_mostly corruption_check_period = 60; /* seconds */

अटल काष्ठा scan_area अणु
	u64 addr;
	u64 size;
पूर्ण scan_areas[MAX_SCAN_AREAS];
अटल पूर्णांक num_scan_areas;

अटल __init पूर्णांक set_corruption_check(अक्षर *arg)
अणु
	sमाप_प्रकार ret;
	अचिन्हित दीर्घ val;

	अगर (!arg) अणु
		pr_err("memory_corruption_check config string not provided\n");
		वापस -EINVAL;
	पूर्ण

	ret = kम_से_अदीर्घ(arg, 10, &val);
	अगर (ret)
		वापस ret;

	memory_corruption_check = val;

	वापस 0;
पूर्ण
early_param("memory_corruption_check", set_corruption_check);

अटल __init पूर्णांक set_corruption_check_period(अक्षर *arg)
अणु
	sमाप_प्रकार ret;
	अचिन्हित दीर्घ val;

	अगर (!arg) अणु
		pr_err("memory_corruption_check_period config string not provided\n");
		वापस -EINVAL;
	पूर्ण

	ret = kम_से_अदीर्घ(arg, 10, &val);
	अगर (ret)
		वापस ret;

	corruption_check_period = val;
	वापस 0;
पूर्ण
early_param("memory_corruption_check_period", set_corruption_check_period);

अटल __init पूर्णांक set_corruption_check_size(अक्षर *arg)
अणु
	अक्षर *end;
	अचिन्हित size;

	अगर (!arg) अणु
		pr_err("memory_corruption_check_size config string not provided\n");
		वापस -EINVAL;
	पूर्ण

	size = memparse(arg, &end);

	अगर (*end == '\0')
		corruption_check_size = size;

	वापस (size == corruption_check_size) ? 0 : -EINVAL;
पूर्ण
early_param("memory_corruption_check_size", set_corruption_check_size);


व्योम __init setup_bios_corruption_check(व्योम)
अणु
	phys_addr_t start, end;
	u64 i;

	अगर (memory_corruption_check == -1) अणु
		memory_corruption_check =
#अगर_घोषित CONFIG_X86_BOOTPARAM_MEMORY_CORRUPTION_CHECK
			1
#अन्यथा
			0
#पूर्ण_अगर
			;
	पूर्ण

	अगर (corruption_check_size == 0)
		memory_corruption_check = 0;

	अगर (!memory_corruption_check)
		वापस;

	corruption_check_size = round_up(corruption_check_size, PAGE_SIZE);

	क्रम_each_मुक्त_mem_range(i, NUMA_NO_NODE, MEMBLOCK_NONE, &start, &end,
				शून्य) अणु
		start = clamp_t(phys_addr_t, round_up(start, PAGE_SIZE),
				PAGE_SIZE, corruption_check_size);
		end = clamp_t(phys_addr_t, round_करोwn(end, PAGE_SIZE),
			      PAGE_SIZE, corruption_check_size);
		अगर (start >= end)
			जारी;

		memblock_reserve(start, end - start);
		scan_areas[num_scan_areas].addr = start;
		scan_areas[num_scan_areas].size = end - start;

		/* Assume we've alपढ़ोy mapped this early memory */
		स_रखो(__va(start), 0, end - start);

		अगर (++num_scan_areas >= MAX_SCAN_AREAS)
			अवरोध;
	पूर्ण

	अगर (num_scan_areas)
		pr_info("Scanning %d areas for low memory corruption\n", num_scan_areas);
पूर्ण


अटल व्योम check_क्रम_bios_corruption(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक corruption = 0;

	अगर (!memory_corruption_check)
		वापस;

	क्रम (i = 0; i < num_scan_areas; i++) अणु
		अचिन्हित दीर्घ *addr = __va(scan_areas[i].addr);
		अचिन्हित दीर्घ size = scan_areas[i].size;

		क्रम (; size; addr++, size -= माप(अचिन्हित दीर्घ)) अणु
			अगर (!*addr)
				जारी;
			pr_err("Corrupted low memory at %p (%lx phys) = %08lx\n", addr, __pa(addr), *addr);
			corruption = 1;
			*addr = 0;
		पूर्ण
	पूर्ण

	WARN_ONCE(corruption, KERN_ERR "Memory corruption detected in low memory\n");
पूर्ण

अटल व्योम check_corruption(काष्ठा work_काष्ठा *dummy);
अटल DECLARE_DELAYED_WORK(bios_check_work, check_corruption);

अटल व्योम check_corruption(काष्ठा work_काष्ठा *dummy)
अणु
	check_क्रम_bios_corruption();
	schedule_delayed_work(&bios_check_work,
		round_jअगरfies_relative(corruption_check_period*HZ));
पूर्ण

अटल पूर्णांक start_periodic_check_क्रम_corruption(व्योम)
अणु
	अगर (!num_scan_areas || !memory_corruption_check || corruption_check_period == 0)
		वापस 0;

	pr_info("Scanning for low memory corruption every %d seconds\n", corruption_check_period);

	/* First समय we run the checks right away */
	schedule_delayed_work(&bios_check_work, 0);

	वापस 0;
पूर्ण
device_initcall(start_periodic_check_क्रम_corruption);

