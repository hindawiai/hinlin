<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Speed Select -- Enumerate and control features
 * Copyright (c) 2019 Intel Corporation.
 */

#समावेश <linux/isst_अगर.h>

#समावेश "isst.h"

काष्ठा process_cmd_काष्ठा अणु
	अक्षर *feature;
	अक्षर *command;
	व्योम (*process_fn)(पूर्णांक arg);
	पूर्णांक arg;
पूर्ण;

अटल स्थिर अक्षर *version_str = "v1.9";
अटल स्थिर पूर्णांक supported_api_ver = 1;
अटल काष्ठा isst_अगर_platक्रमm_info isst_platक्रमm_info;
अटल अक्षर *progname;
अटल पूर्णांक debug_flag;
अटल खाता *outf;

अटल पूर्णांक cpu_model;
अटल पूर्णांक cpu_stepping;

#घोषणा MAX_CPUS_IN_ONE_REQ 256
अटल लघु max_target_cpus;
अटल अचिन्हित लघु target_cpus[MAX_CPUS_IN_ONE_REQ];

अटल पूर्णांक topo_max_cpus;
अटल माप_प्रकार present_cpumask_size;
अटल cpu_set_t *present_cpumask;
अटल माप_प्रकार target_cpumask_size;
अटल cpu_set_t *target_cpumask;
अटल पूर्णांक tdp_level = 0xFF;
अटल पूर्णांक fact_bucket = 0xFF;
अटल पूर्णांक fact_avx = 0xFF;
अटल अचिन्हित दीर्घ दीर्घ fact_trl;
अटल पूर्णांक out_क्रमmat_json;
अटल पूर्णांक cmd_help;
अटल पूर्णांक क्रमce_online_offline;
अटल पूर्णांक स्वतः_mode;
अटल पूर्णांक fact_enable_fail;

अटल पूर्णांक mbox_delay;
अटल पूर्णांक mbox_retries = 3;

/* clos related */
अटल पूर्णांक current_clos = -1;
अटल पूर्णांक clos_epp = -1;
अटल पूर्णांक clos_prop_prio = -1;
अटल पूर्णांक clos_min = -1;
अटल पूर्णांक clos_max = -1;
अटल पूर्णांक clos_desired = -1;
अटल पूर्णांक clos_priority_type;

काष्ठा _cpu_map अणु
	अचिन्हित लघु core_id;
	अचिन्हित लघु pkg_id;
	अचिन्हित लघु die_id;
	अचिन्हित लघु punit_cpu;
	अचिन्हित लघु punit_cpu_core;
पूर्ण;
काष्ठा _cpu_map *cpu_map;

काष्ठा cpu_topology अणु
	लघु cpu;
	लघु core_id;
	लघु pkg_id;
	लघु die_id;
पूर्ण;

खाता *get_output_file(व्योम)
अणु
	वापस outf;
पूर्ण

व्योम debug_म_लिखो(स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	अगर (debug_flag)
		भ_लिखो(क्रमmat, args);

	बहु_पूर्ण(args);
पूर्ण


पूर्णांक is_clx_n_platक्रमm(व्योम)
अणु
	अगर (cpu_model == 0x55)
		अगर (cpu_stepping == 0x6 || cpu_stepping == 0x7)
			वापस 1;
	वापस 0;
पूर्ण

पूर्णांक is_skx_based_platक्रमm(व्योम)
अणु
	अगर (cpu_model == 0x55)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक update_cpu_model(व्योम)
अणु
	अचिन्हित पूर्णांक ebx, ecx, edx;
	अचिन्हित पूर्णांक fms, family;

	__cpuid(1, fms, ebx, ecx, edx);
	family = (fms >> 8) & 0xf;
	cpu_model = (fms >> 4) & 0xf;
	अगर (family == 6 || family == 0xf)
		cpu_model += ((fms >> 16) & 0xf) << 4;

	cpu_stepping = fms & 0xf;
	/* only three CascadeLake-N models are supported */
	अगर (is_clx_n_platक्रमm()) अणु
		खाता *fp;
		माप_प्रकार n = 0;
		अक्षर *line = शून्य;
		पूर्णांक ret = 1;

		fp = ख_खोलो("/proc/cpuinfo", "r");
		अगर (!fp)
			err(-1, "cannot open /proc/cpuinfo\n");

		जबतक (getline(&line, &n, fp) > 0) अणु
			अगर (म_माला(line, "model name")) अणु
				अगर (म_माला(line, "6252N") ||
				    म_माला(line, "6230N") ||
				    म_माला(line, "5218N"))
					ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		मुक्त(line);
		ख_बंद(fp);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* Open a file, and निकास on failure */
अटल खाता *ख_खोलो_or_निकास(स्थिर अक्षर *path, स्थिर अक्षर *mode)
अणु
	खाता *filep = ख_खोलो(path, mode);

	अगर (!filep)
		err(1, "%s: open failed", path);

	वापस filep;
पूर्ण

/* Parse a file containing a single पूर्णांक */
अटल पूर्णांक parse_पूर्णांक_file(पूर्णांक fatal, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर path[PATH_MAX];
	खाता *filep;
	पूर्णांक value;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(path, माप(path), fmt, args);
	बहु_पूर्ण(args);
	अगर (fatal) अणु
		filep = ख_खोलो_or_निकास(path, "r");
	पूर्ण अन्यथा अणु
		filep = ख_खोलो(path, "r");
		अगर (!filep)
			वापस -1;
	पूर्ण
	अगर (ख_पूछो(filep, "%d", &value) != 1)
		err(1, "%s: failed to parse number from file", path);
	ख_बंद(filep);

	वापस value;
पूर्ण

पूर्णांक cpufreq_sysfs_present(व्योम)
अणु
	सूची *dir;

	dir = सूची_खोलो("/sys/devices/system/cpu/cpu0/cpufreq");
	अगर (dir) अणु
		बंद_सूची(dir);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक out_क्रमmat_is_json(व्योम)
अणु
	वापस out_क्रमmat_json;
पूर्ण

अटल पूर्णांक get_stored_topology_info(पूर्णांक cpu, पूर्णांक *core_id, पूर्णांक *pkg_id, पूर्णांक *die_id)
अणु
	स्थिर अक्षर *pathname = "/var/run/isst_cpu_topology.dat";
	काष्ठा cpu_topology cpu_top;
	खाता *fp;
	पूर्णांक ret;

	fp = ख_खोलो(pathname, "rb");
	अगर (!fp)
		वापस -1;

	ret = ख_जाओ(fp, cpu * माप(cpu_top), शुरू_से);
	अगर (ret)
		जाओ err_ret;

	ret = ख_पढ़ो(&cpu_top, माप(cpu_top), 1, fp);
	अगर (ret != 1) अणु
		ret = -1;
		जाओ err_ret;
	पूर्ण

	*pkg_id = cpu_top.pkg_id;
	*core_id = cpu_top.core_id;
	*die_id = cpu_top.die_id;
	ret = 0;

err_ret:
	ख_बंद(fp);

	वापस ret;
पूर्ण

अटल व्योम store_cpu_topology(व्योम)
अणु
	स्थिर अक्षर *pathname = "/var/run/isst_cpu_topology.dat";
	खाता *fp;
	पूर्णांक i;

	fp = ख_खोलो(pathname, "rb");
	अगर (fp) अणु
		/* Mapping alपढ़ोy exists */
		ख_बंद(fp);
		वापस;
	पूर्ण

	fp = ख_खोलो(pathname, "wb");
	अगर (!fp) अणु
		ख_लिखो(मानक_त्रुटि, "Can't create file:%s\n", pathname);
		वापस;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "Caching topology information\n");

	क्रम (i = 0; i < topo_max_cpus; ++i) अणु
		काष्ठा cpu_topology cpu_top;

		cpu_top.core_id = parse_पूर्णांक_file(0,
			"/sys/devices/system/cpu/cpu%d/topology/core_id", i);
		अगर (cpu_top.core_id < 0)
			cpu_top.core_id = -1;

		cpu_top.pkg_id = parse_पूर्णांक_file(0,
			"/sys/devices/system/cpu/cpu%d/topology/physical_package_id", i);
		अगर (cpu_top.pkg_id < 0)
			cpu_top.pkg_id = -1;

		cpu_top.die_id = parse_पूर्णांक_file(0,
			"/sys/devices/system/cpu/cpu%d/topology/die_id", i);
		अगर (cpu_top.die_id < 0)
			cpu_top.die_id = -1;

		cpu_top.cpu = i;

		अगर (ख_डालो(&cpu_top, माप(cpu_top), 1, fp) != 1) अणु
			ख_लिखो(मानक_त्रुटि, "Can't write to:%s\n", pathname);
			अवरोध;
		पूर्ण
	पूर्ण

	ख_बंद(fp);
पूर्ण

पूर्णांक get_physical_package_id(पूर्णांक cpu)
अणु
	पूर्णांक ret;

	ret = parse_पूर्णांक_file(0,
			"/sys/devices/system/cpu/cpu%d/topology/physical_package_id",
			cpu);
	अगर (ret < 0) अणु
		पूर्णांक core_id, pkg_id, die_id;

		ret = get_stored_topology_info(cpu, &core_id, &pkg_id, &die_id);
		अगर (!ret)
			वापस pkg_id;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक get_physical_core_id(पूर्णांक cpu)
अणु
	पूर्णांक ret;

	ret = parse_पूर्णांक_file(0,
			"/sys/devices/system/cpu/cpu%d/topology/core_id",
			cpu);
	अगर (ret < 0) अणु
		पूर्णांक core_id, pkg_id, die_id;

		ret = get_stored_topology_info(cpu, &core_id, &pkg_id, &die_id);
		अगर (!ret)
			वापस core_id;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक get_physical_die_id(पूर्णांक cpu)
अणु
	पूर्णांक ret;

	ret = parse_पूर्णांक_file(0,
			"/sys/devices/system/cpu/cpu%d/topology/die_id",
			cpu);
	अगर (ret < 0) अणु
		पूर्णांक core_id, pkg_id, die_id;

		ret = get_stored_topology_info(cpu, &core_id, &pkg_id, &die_id);
		अगर (!ret) अणु
			अगर (die_id < 0)
				die_id = 0;

			वापस die_id;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		ret = 0;

	वापस ret;
पूर्ण

पूर्णांक get_cpufreq_base_freq(पूर्णांक cpu)
अणु
	वापस parse_पूर्णांक_file(0, "/sys/devices/system/cpu/cpu%d/cpufreq/base_frequency", cpu);
पूर्ण

पूर्णांक get_topo_max_cpus(व्योम)
अणु
	वापस topo_max_cpus;
पूर्ण

अटल व्योम set_cpu_online_offline(पूर्णांक cpu, पूर्णांक state)
अणु
	अक्षर buffer[128];
	पूर्णांक fd, ret;

	snम_लिखो(buffer, माप(buffer),
		 "/sys/devices/system/cpu/cpu%d/online", cpu);

	fd = खोलो(buffer, O_WRONLY);
	अगर (fd < 0) अणु
		अगर (!cpu && state) अणु
			ख_लिखो(मानक_त्रुटि, "This system is not configured for CPU 0 online/offline\n");
			ख_लिखो(मानक_त्रुटि, "Ignoring online request for CPU 0 as this is already online\n");
			वापस;
		पूर्ण
		err(-1, "%s open failed", buffer);
	पूर्ण

	अगर (state)
		ret = ग_लिखो(fd, "1\n", 2);
	अन्यथा
		ret = ग_लिखो(fd, "0\n", 2);

	अगर (ret == -1)
		लिखो_त्रुटि("Online/Offline: Operation failed\n");

	बंद(fd);
पूर्ण

अटल व्योम क्रमce_all_cpus_online(व्योम)
अणु
	पूर्णांक i;

	ख_लिखो(मानक_त्रुटि, "Forcing all CPUs online\n");

	क्रम (i = 0; i < topo_max_cpus; ++i)
		set_cpu_online_offline(i, 1);

	unlink("/var/run/isst_cpu_topology.dat");
पूर्ण

#घोषणा MAX_PACKAGE_COUNT 8
#घोषणा MAX_DIE_PER_PACKAGE 2
अटल व्योम क्रम_each_online_package_in_set(व्योम (*callback)(पूर्णांक, व्योम *, व्योम *,
							    व्योम *, व्योम *),
					   व्योम *arg1, व्योम *arg2, व्योम *arg3,
					   व्योम *arg4)
अणु
	पूर्णांक max_packages[MAX_PACKAGE_COUNT * MAX_PACKAGE_COUNT];
	पूर्णांक pkg_index = 0, i;

	स_रखो(max_packages, 0xff, माप(max_packages));
	क्रम (i = 0; i < topo_max_cpus; ++i) अणु
		पूर्णांक j, online, pkg_id, die_id = 0, skip = 0;

		अगर (!CPU_ISSET_S(i, present_cpumask_size, present_cpumask))
			जारी;
		अगर (i)
			online = parse_पूर्णांक_file(
				1, "/sys/devices/system/cpu/cpu%d/online", i);
		अन्यथा
			online =
				1; /* online entry क्रम CPU 0 needs some special configs */

		die_id = get_physical_die_id(i);
		अगर (die_id < 0)
			die_id = 0;

		pkg_id = parse_पूर्णांक_file(0,
			"/sys/devices/system/cpu/cpu%d/topology/physical_package_id", i);
		अगर (pkg_id < 0)
			जारी;

		/* Create an unique id क्रम package, die combination to store */
		pkg_id = (MAX_PACKAGE_COUNT * pkg_id + die_id);

		क्रम (j = 0; j < pkg_index; ++j) अणु
			अगर (max_packages[j] == pkg_id) अणु
				skip = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!skip && online && callback) अणु
			callback(i, arg1, arg2, arg3, arg4);
			max_packages[pkg_index++] = pkg_id;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम क्रम_each_online_target_cpu_in_set(
	व्योम (*callback)(पूर्णांक, व्योम *, व्योम *, व्योम *, व्योम *), व्योम *arg1,
	व्योम *arg2, व्योम *arg3, व्योम *arg4)
अणु
	पूर्णांक i, found = 0;

	क्रम (i = 0; i < topo_max_cpus; ++i) अणु
		पूर्णांक online;

		अगर (!CPU_ISSET_S(i, target_cpumask_size, target_cpumask))
			जारी;
		अगर (i)
			online = parse_पूर्णांक_file(
				1, "/sys/devices/system/cpu/cpu%d/online", i);
		अन्यथा
			online =
				1; /* online entry क्रम CPU 0 needs some special configs */

		अगर (online && callback) अणु
			callback(i, arg1, arg2, arg3, arg4);
			found = 1;
		पूर्ण
	पूर्ण

	अगर (!found)
		ख_लिखो(मानक_त्रुटि, "No valid CPU in the list\n");
पूर्ण

#घोषणा BITMASK_SIZE 32
अटल व्योम set_max_cpu_num(व्योम)
अणु
	खाता *filep;
	अचिन्हित दीर्घ dummy;
	पूर्णांक i;

	topo_max_cpus = 0;
	क्रम (i = 0; i < 256; ++i) अणु
		अक्षर path[256];

		snम_लिखो(path, माप(path),
			 "/sys/devices/system/cpu/cpu%d/topology/thread_siblings", i);
		filep = ख_खोलो(path, "r");
		अगर (filep)
			अवरोध;
	पूर्ण

	अगर (!filep) अणु
		ख_लिखो(मानक_त्रुटि, "Can't get max cpu number\n");
		निकास(0);
	पूर्ण

	जबतक (ख_पूछो(filep, "%lx,", &dummy) == 1)
		topo_max_cpus += BITMASK_SIZE;
	ख_बंद(filep);

	debug_म_लिखो("max cpus %d\n", topo_max_cpus);
पूर्ण

माप_प्रकार alloc_cpu_set(cpu_set_t **cpu_set)
अणु
	cpu_set_t *_cpu_set;
	माप_प्रकार size;

	_cpu_set = CPU_ALLOC((topo_max_cpus + 1));
	अगर (_cpu_set == शून्य)
		err(3, "CPU_ALLOC");
	size = CPU_ALLOC_SIZE((topo_max_cpus + 1));
	CPU_ZERO_S(size, _cpu_set);

	*cpu_set = _cpu_set;
	वापस size;
पूर्ण

व्योम मुक्त_cpu_set(cpu_set_t *cpu_set)
अणु
	CPU_FREE(cpu_set);
पूर्ण

अटल पूर्णांक cpu_cnt[MAX_PACKAGE_COUNT][MAX_DIE_PER_PACKAGE];
अटल दीर्घ दीर्घ core_mask[MAX_PACKAGE_COUNT][MAX_DIE_PER_PACKAGE];
अटल व्योम set_cpu_present_cpu_mask(व्योम)
अणु
	माप_प्रकार size;
	सूची *dir;
	पूर्णांक i;

	size = alloc_cpu_set(&present_cpumask);
	present_cpumask_size = size;
	क्रम (i = 0; i < topo_max_cpus; ++i) अणु
		अक्षर buffer[256];

		snम_लिखो(buffer, माप(buffer),
			 "/sys/devices/system/cpu/cpu%d", i);
		dir = सूची_खोलो(buffer);
		अगर (dir) अणु
			पूर्णांक pkg_id, die_id;

			CPU_SET_S(i, size, present_cpumask);
			die_id = get_physical_die_id(i);
			अगर (die_id < 0)
				die_id = 0;

			pkg_id = get_physical_package_id(i);
			अगर (pkg_id < 0) अणु
				ख_लिखो(मानक_त्रुटि, "Failed to get package id, CPU %d may be offline\n", i);
				जारी;
			पूर्ण
			अगर (pkg_id < MAX_PACKAGE_COUNT &&
			    die_id < MAX_DIE_PER_PACKAGE) अणु
				पूर्णांक core_id = get_physical_core_id(i);

				cpu_cnt[pkg_id][die_id]++;
				core_mask[pkg_id][die_id] |= (1ULL << core_id);
			पूर्ण
		पूर्ण
		बंद_सूची(dir);
	पूर्ण
पूर्ण

पूर्णांक get_max_punit_core_id(पूर्णांक pkg_id, पूर्णांक die_id)
अणु
	पूर्णांक max_id = 0;
	पूर्णांक i;

	क्रम (i = 0; i < topo_max_cpus; ++i)
	अणु
		अगर (!CPU_ISSET_S(i, present_cpumask_size, present_cpumask))
			जारी;

		अगर (cpu_map[i].pkg_id == pkg_id &&
			cpu_map[i].die_id == die_id &&
			cpu_map[i].punit_cpu_core > max_id)
			max_id = cpu_map[i].punit_cpu_core;
	पूर्ण

	वापस max_id;
पूर्ण

पूर्णांक get_cpu_count(पूर्णांक pkg_id, पूर्णांक die_id)
अणु
	अगर (pkg_id < MAX_PACKAGE_COUNT && die_id < MAX_DIE_PER_PACKAGE)
		वापस cpu_cnt[pkg_id][die_id];

	वापस 0;
पूर्ण

अटल व्योम set_cpu_target_cpu_mask(व्योम)
अणु
	माप_प्रकार size;
	पूर्णांक i;

	size = alloc_cpu_set(&target_cpumask);
	target_cpumask_size = size;
	क्रम (i = 0; i < max_target_cpus; ++i) अणु
		अगर (!CPU_ISSET_S(target_cpus[i], present_cpumask_size,
				 present_cpumask))
			जारी;

		CPU_SET_S(target_cpus[i], size, target_cpumask);
	पूर्ण
पूर्ण

अटल व्योम create_cpu_map(व्योम)
अणु
	स्थिर अक्षर *pathname = "/dev/isst_interface";
	पूर्णांक i, fd = 0;
	काष्ठा isst_अगर_cpu_maps map;

	cpu_map = दो_स्मृति(माप(*cpu_map) * topo_max_cpus);
	अगर (!cpu_map)
		err(3, "cpumap");

	fd = खोलो(pathname, O_RDWR);
	अगर (fd < 0)
		err(-1, "%s open failed", pathname);

	क्रम (i = 0; i < topo_max_cpus; ++i) अणु
		अगर (!CPU_ISSET_S(i, present_cpumask_size, present_cpumask))
			जारी;

		map.cmd_count = 1;
		map.cpu_map[0].logical_cpu = i;

		debug_म_लिखो(" map logical_cpu:%d\n",
			     map.cpu_map[0].logical_cpu);
		अगर (ioctl(fd, ISST_IF_GET_PHY_ID, &map) == -1) अणु
			लिखो_त्रुटि("ISST_IF_GET_PHY_ID");
			ख_लिखो(outf, "Error: map logical_cpu:%d\n",
				map.cpu_map[0].logical_cpu);
			जारी;
		पूर्ण
		cpu_map[i].core_id = get_physical_core_id(i);
		cpu_map[i].pkg_id = get_physical_package_id(i);
		cpu_map[i].die_id = get_physical_die_id(i);
		cpu_map[i].punit_cpu = map.cpu_map[0].physical_cpu;
		cpu_map[i].punit_cpu_core = (map.cpu_map[0].physical_cpu >>
					     1); // shअगरt to get core id

		debug_म_लिखो(
			"map logical_cpu:%d core: %d die:%d pkg:%d punit_cpu:%d punit_core:%d\n",
			i, cpu_map[i].core_id, cpu_map[i].die_id,
			cpu_map[i].pkg_id, cpu_map[i].punit_cpu,
			cpu_map[i].punit_cpu_core);
	पूर्ण

	अगर (fd)
		बंद(fd);
पूर्ण

पूर्णांक find_logical_cpu(पूर्णांक pkg_id, पूर्णांक die_id, पूर्णांक punit_core_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < topo_max_cpus; ++i) अणु
		अगर (cpu_map[i].pkg_id == pkg_id &&
		    cpu_map[i].die_id == die_id &&
		    cpu_map[i].punit_cpu_core == punit_core_id)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

व्योम set_cpu_mask_from_punit_coremask(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ core_mask,
				      माप_प्रकार core_cpumask_size,
				      cpu_set_t *core_cpumask, पूर्णांक *cpu_cnt)
अणु
	पूर्णांक i, cnt = 0;
	पूर्णांक die_id, pkg_id;

	*cpu_cnt = 0;
	die_id = get_physical_die_id(cpu);
	pkg_id = get_physical_package_id(cpu);

	क्रम (i = 0; i < 64; ++i) अणु
		अगर (core_mask & BIT_ULL(i)) अणु
			पूर्णांक j;

			क्रम (j = 0; j < topo_max_cpus; ++j) अणु
				अगर (!CPU_ISSET_S(j, present_cpumask_size, present_cpumask))
					जारी;

				अगर (cpu_map[j].pkg_id == pkg_id &&
				    cpu_map[j].die_id == die_id &&
				    cpu_map[j].punit_cpu_core == i) अणु
					CPU_SET_S(j, core_cpumask_size,
						  core_cpumask);
					++cnt;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	*cpu_cnt = cnt;
पूर्ण

पूर्णांक find_phy_core_num(पूर्णांक logical_cpu)
अणु
	अगर (logical_cpu < topo_max_cpus)
		वापस cpu_map[logical_cpu].punit_cpu_core;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक isst_send_mmio_command(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक reg, पूर्णांक ग_लिखो,
				  अचिन्हित पूर्णांक *value)
अणु
	काष्ठा isst_अगर_io_regs io_regs;
	स्थिर अक्षर *pathname = "/dev/isst_interface";
	पूर्णांक cmd;
	पूर्णांक fd;

	debug_म_लिखो("mmio_cmd cpu:%d reg:%d write:%d\n", cpu, reg, ग_लिखो);

	fd = खोलो(pathname, O_RDWR);
	अगर (fd < 0)
		err(-1, "%s open failed", pathname);

	io_regs.req_count = 1;
	io_regs.io_reg[0].logical_cpu = cpu;
	io_regs.io_reg[0].reg = reg;
	cmd = ISST_IF_IO_CMD;
	अगर (ग_लिखो) अणु
		io_regs.io_reg[0].पढ़ो_ग_लिखो = 1;
		io_regs.io_reg[0].value = *value;
	पूर्ण अन्यथा अणु
		io_regs.io_reg[0].पढ़ो_ग_लिखो = 0;
	पूर्ण

	अगर (ioctl(fd, cmd, &io_regs) == -1) अणु
		अगर (त्रुटि_सं == ENOTTY) अणु
			लिखो_त्रुटि("ISST_IF_IO_COMMAND\n");
			ख_लिखो(मानक_त्रुटि, "Check presence of kernel modules: isst_if_mmio\n");
			निकास(0);
		पूर्ण
		ख_लिखो(outf, "Error: mmio_cmd cpu:%d reg:%x read_write:%x\n",
			cpu, reg, ग_लिखो);
	पूर्ण अन्यथा अणु
		अगर (!ग_लिखो)
			*value = io_regs.io_reg[0].value;

		debug_म_लिखो(
			"mmio_cmd response: cpu:%d reg:%x rd_write:%x resp:%x\n",
			cpu, reg, ग_लिखो, *value);
	पूर्ण

	बंद(fd);

	वापस 0;
पूर्ण

पूर्णांक isst_send_mbox_command(अचिन्हित पूर्णांक cpu, अचिन्हित अक्षर command,
			   अचिन्हित अक्षर sub_command, अचिन्हित पूर्णांक parameter,
			   अचिन्हित पूर्णांक req_data, अचिन्हित पूर्णांक *resp)
अणु
	स्थिर अक्षर *pathname = "/dev/isst_interface";
	पूर्णांक fd, retry;
	काष्ठा isst_अगर_mbox_cmds mbox_cmds = अणु 0 पूर्ण;

	debug_म_लिखो(
		"mbox_send: cpu:%d command:%x sub_command:%x parameter:%x req_data:%x\n",
		cpu, command, sub_command, parameter, req_data);

	अगर (!is_skx_based_platक्रमm() && command == CONFIG_CLOS &&
	    sub_command != CLOS_PM_QOS_CONFIG) अणु
		अचिन्हित पूर्णांक value;
		पूर्णांक ग_लिखो = 0;
		पूर्णांक clos_id, core_id, ret = 0;

		debug_म_लिखो("CPU %d\n", cpu);

		अगर (parameter & BIT(MBOX_CMD_WRITE_BIT)) अणु
			value = req_data;
			ग_लिखो = 1;
		पूर्ण

		चयन (sub_command) अणु
		हाल CLOS_PQR_ASSOC:
			core_id = parameter & 0xff;
			ret = isst_send_mmio_command(
				cpu, PQR_ASSOC_OFFSET + core_id * 4, ग_लिखो,
				&value);
			अगर (!ret && !ग_लिखो)
				*resp = value;
			अवरोध;
		हाल CLOS_PM_CLOS:
			clos_id = parameter & 0x03;
			ret = isst_send_mmio_command(
				cpu, PM_CLOS_OFFSET + clos_id * 4, ग_लिखो,
				&value);
			अगर (!ret && !ग_लिखो)
				*resp = value;
			अवरोध;
		हाल CLOS_STATUS:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		वापस ret;
	पूर्ण

	mbox_cmds.cmd_count = 1;
	mbox_cmds.mbox_cmd[0].logical_cpu = cpu;
	mbox_cmds.mbox_cmd[0].command = command;
	mbox_cmds.mbox_cmd[0].sub_command = sub_command;
	mbox_cmds.mbox_cmd[0].parameter = parameter;
	mbox_cmds.mbox_cmd[0].req_data = req_data;

	अगर (mbox_delay)
		usleep(mbox_delay * 1000);

	fd = खोलो(pathname, O_RDWR);
	अगर (fd < 0)
		err(-1, "%s open failed", pathname);

	retry = mbox_retries;

	करो अणु
		अगर (ioctl(fd, ISST_IF_MBOX_COMMAND, &mbox_cmds) == -1) अणु
			अगर (त्रुटि_सं == ENOTTY) अणु
				लिखो_त्रुटि("ISST_IF_MBOX_COMMAND\n");
				ख_लिखो(मानक_त्रुटि, "Check presence of kernel modules: isst_if_mbox_pci or isst_if_mbox_msr\n");
				निकास(0);
			पूर्ण
			debug_म_लिखो(
				"Error: mbox_cmd cpu:%d command:%x sub_command:%x parameter:%x req_data:%x errorno:%d\n",
				cpu, command, sub_command, parameter, req_data, त्रुटि_सं);
			--retry;
		पूर्ण अन्यथा अणु
			*resp = mbox_cmds.mbox_cmd[0].resp_data;
			debug_म_लिखो(
				"mbox_cmd response: cpu:%d command:%x sub_command:%x parameter:%x req_data:%x resp:%x\n",
				cpu, command, sub_command, parameter, req_data, *resp);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (retry);

	बंद(fd);

	अगर (!retry) अणु
		debug_म_लिखो("Failed mbox command even after retries\n");
		वापस -1;

	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक isst_send_msr_command(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक msr, पूर्णांक ग_लिखो,
			  अचिन्हित दीर्घ दीर्घ *req_resp)
अणु
	काष्ठा isst_अगर_msr_cmds msr_cmds;
	स्थिर अक्षर *pathname = "/dev/isst_interface";
	पूर्णांक fd;

	fd = खोलो(pathname, O_RDWR);
	अगर (fd < 0)
		err(-1, "%s open failed", pathname);

	msr_cmds.cmd_count = 1;
	msr_cmds.msr_cmd[0].logical_cpu = cpu;
	msr_cmds.msr_cmd[0].msr = msr;
	msr_cmds.msr_cmd[0].पढ़ो_ग_लिखो = ग_लिखो;
	अगर (ग_लिखो)
		msr_cmds.msr_cmd[0].data = *req_resp;

	अगर (ioctl(fd, ISST_IF_MSR_COMMAND, &msr_cmds) == -1) अणु
		लिखो_त्रुटि("ISST_IF_MSR_COMMAND");
		ख_लिखो(outf, "Error: msr_cmd cpu:%d msr:%x read_write:%d\n",
			cpu, msr, ग_लिखो);
	पूर्ण अन्यथा अणु
		अगर (!ग_लिखो)
			*req_resp = msr_cmds.msr_cmd[0].data;

		debug_म_लिखो(
			"msr_cmd response: cpu:%d msr:%x rd_write:%x resp:%llx %llx\n",
			cpu, msr, ग_लिखो, *req_resp, msr_cmds.msr_cmd[0].data);
	पूर्ण

	बंद(fd);

	वापस 0;
पूर्ण

अटल पूर्णांक isst_fill_platक्रमm_info(व्योम)
अणु
	स्थिर अक्षर *pathname = "/dev/isst_interface";
	पूर्णांक fd;

	fd = खोलो(pathname, O_RDWR);
	अगर (fd < 0)
		err(-1, "%s open failed", pathname);

	अगर (ioctl(fd, ISST_IF_GET_PLATFORM_INFO, &isst_platक्रमm_info) == -1) अणु
		लिखो_त्रुटि("ISST_IF_GET_PLATFORM_INFO");
		बंद(fd);
		वापस -1;
	पूर्ण

	बंद(fd);

	अगर (isst_platक्रमm_info.api_version > supported_api_ver) अणु
		म_लिखो("Incompatible API versions; Upgrade of tool is required\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम isst_prपूर्णांक_extended_platक्रमm_info(व्योम)
अणु
	पूर्णांक cp_state, cp_cap, fact_support = 0, pbf_support = 0;
	काष्ठा isst_pkg_ctdp_level_info ctdp_level;
	काष्ठा isst_pkg_ctdp pkg_dev;
	पूर्णांक ret, i, j;
	खाता *filep;

	क्रम (i = 0; i < 256; ++i) अणु
		अक्षर path[256];

		snम_लिखो(path, माप(path),
			 "/sys/devices/system/cpu/cpu%d/topology/thread_siblings", i);
		filep = ख_खोलो(path, "r");
		अगर (filep)
			अवरोध;
	पूर्ण

	अगर (!filep)
		वापस;

	ख_बंद(filep);

	ret = isst_get_ctdp_levels(i, &pkg_dev);
	अगर (ret)
		वापस;

	अगर (pkg_dev.enabled) अणु
		ख_लिखो(outf, "Intel(R) SST-PP (feature perf-profile) is supported\n");
	पूर्ण अन्यथा अणु
		ख_लिखो(outf, "Intel(R) SST-PP (feature perf-profile) is not supported\n");
		ख_लिखो(outf, "Only performance level 0 (base level) is present\n");
	पूर्ण

	अगर (pkg_dev.locked)
		ख_लिखो(outf, "TDP level change control is locked\n");
	अन्यथा
		ख_लिखो(outf, "TDP level change control is unlocked, max level: %d \n", pkg_dev.levels);

	क्रम (j = 0; j <= pkg_dev.levels; ++j) अणु
		ret = isst_get_ctdp_control(i, j, &ctdp_level);
		अगर (ret)
			जारी;

		अगर (!fact_support && ctdp_level.fact_support)
			fact_support = 1;

		अगर (!pbf_support && ctdp_level.pbf_support)
			pbf_support = 1;
	पूर्ण

	अगर (fact_support)
		ख_लिखो(outf, "Intel(R) SST-TF (feature turbo-freq) is supported\n");
	अन्यथा
		ख_लिखो(outf, "Intel(R) SST-TF (feature turbo-freq) is not supported\n");

	अगर (pbf_support)
		ख_लिखो(outf, "Intel(R) SST-BF (feature base-freq) is supported\n");
	अन्यथा
		ख_लिखो(outf, "Intel(R) SST-BF (feature base-freq) is not supported\n");

	ret = isst_पढ़ो_pm_config(i, &cp_state, &cp_cap);
	अगर (ret) अणु
		ख_लिखो(outf, "Intel(R) SST-CP (feature core-power) status is unknown\n");
		वापस;
	पूर्ण
	अगर (cp_cap)
		ख_लिखो(outf, "Intel(R) SST-CP (feature core-power) is supported\n");
	अन्यथा
		ख_लिखो(outf, "Intel(R) SST-CP (feature core-power) is not supported\n");
पूर्ण

अटल व्योम isst_prपूर्णांक_platक्रमm_inक्रमmation(व्योम)
अणु
	काष्ठा isst_अगर_platक्रमm_info platक्रमm_info;
	स्थिर अक्षर *pathname = "/dev/isst_interface";
	पूर्णांक fd;

	अगर (is_clx_n_platक्रमm()) अणु
		ख_लिखो(मानक_त्रुटि, "\nThis option in not supported on this platform\n");
		निकास(0);
	पूर्ण

	fd = खोलो(pathname, O_RDWR);
	अगर (fd < 0)
		err(-1, "%s open failed", pathname);

	अगर (ioctl(fd, ISST_IF_GET_PLATFORM_INFO, &platक्रमm_info) == -1) अणु
		लिखो_त्रुटि("ISST_IF_GET_PLATFORM_INFO");
	पूर्ण अन्यथा अणु
		ख_लिखो(outf, "Platform: API version : %d\n",
			platक्रमm_info.api_version);
		ख_लिखो(outf, "Platform: Driver version : %d\n",
			platक्रमm_info.driver_version);
		ख_लिखो(outf, "Platform: mbox supported : %d\n",
			platक्रमm_info.mbox_supported);
		ख_लिखो(outf, "Platform: mmio supported : %d\n",
			platक्रमm_info.mmio_supported);
		isst_prपूर्णांक_extended_platक्रमm_info();
	पूर्ण

	बंद(fd);

	निकास(0);
पूर्ण

अटल अक्षर *local_str0, *local_str1;
अटल व्योम exec_on_get_ctdp_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
				 व्योम *arg4)
अणु
	पूर्णांक (*fn_ptr)(पूर्णांक cpu, व्योम *arg);
	पूर्णांक ret;

	fn_ptr = arg1;
	ret = fn_ptr(cpu, arg2);
	अगर (ret)
		isst_display_error_info_message(1, "get_tdp_* failed", 0, 0);
	अन्यथा
		isst_ctdp_display_core_info(cpu, outf, arg3,
					    *(अचिन्हित पूर्णांक *)arg4,
					    local_str0, local_str1);
पूर्ण

#घोषणा _get_tdp_level(desc, suffix, object, help, str0, str1)			\
	अटल व्योम get_tdp_##object(पूर्णांक arg)                                    \
	अणु                                                                         \
		काष्ठा isst_pkg_ctdp ctdp;                                        \
\
		अगर (cmd_help) अणु                                                   \
			ख_लिखो(मानक_त्रुटि,                                           \
				"Print %s [No command arguments are required]\n", \
				help);                                            \
			निकास(0);                                                  \
		पूर्ण                                                                 \
		local_str0 = str0;						  \
		local_str1 = str1;						  \
		isst_ctdp_display_inक्रमmation_start(outf);                        \
		अगर (max_target_cpus)                                              \
			क्रम_each_online_target_cpu_in_set(                        \
				exec_on_get_ctdp_cpu, isst_get_ctdp_##suffix,     \
				&ctdp, desc, &ctdp.object);                       \
		अन्यथा                                                              \
			क्रम_each_online_package_in_set(exec_on_get_ctdp_cpu,      \
						       isst_get_ctdp_##suffix,    \
						       &ctdp, desc,               \
						       &ctdp.object);             \
		isst_ctdp_display_inक्रमmation_end(outf);                          \
	पूर्ण

_get_tdp_level("get-config-levels", levels, levels, "Max TDP level", शून्य, शून्य);
_get_tdp_level("get-config-version", levels, version, "TDP version", शून्य, शून्य);
_get_tdp_level("get-config-enabled", levels, enabled, "perf-profile enable status", "disabled", "enabled");
_get_tdp_level("get-config-current_level", levels, current_level,
	       "Current TDP Level", शून्य, शून्य);
_get_tdp_level("get-lock-status", levels, locked, "TDP lock status", "unlocked", "locked");

काष्ठा isst_pkg_ctdp clx_n_pkg_dev;

अटल पूर्णांक clx_n_get_base_ratio(व्योम)
अणु
	खाता *fp;
	अक्षर *begin, *end, *line = शून्य;
	अक्षर number[5];
	भग्न value = 0;
	माप_प्रकार n = 0;

	fp = ख_खोलो("/proc/cpuinfo", "r");
	अगर (!fp)
		err(-1, "cannot open /proc/cpuinfo\n");

	जबतक (getline(&line, &n, fp) > 0) अणु
		अगर (म_माला(line, "model name")) अणु
			/* this is true क्रम CascadeLake-N */
			begin = म_माला(line, "@ ") + 2;
			end = म_माला(line, "GHz");
			म_नकलन(number, begin, end - begin);
			value = म_से_भ(number) * 10;
			अवरोध;
		पूर्ण
	पूर्ण
	मुक्त(line);
	ख_बंद(fp);

	वापस (पूर्णांक)(value);
पूर्ण

अटल पूर्णांक clx_n_config(पूर्णांक cpu)
अणु
	पूर्णांक i, ret, pkg_id, die_id;
	अचिन्हित दीर्घ cpu_bf;
	काष्ठा isst_pkg_ctdp_level_info *ctdp_level;
	काष्ठा isst_pbf_info *pbf_info;

	ctdp_level = &clx_n_pkg_dev.ctdp_level[0];
	pbf_info = &ctdp_level->pbf_info;
	ctdp_level->core_cpumask_size =
			alloc_cpu_set(&ctdp_level->core_cpumask);

	/* find the frequency base ratio */
	ctdp_level->tdp_ratio = clx_n_get_base_ratio();
	अगर (ctdp_level->tdp_ratio == 0) अणु
		debug_म_लिखो("CLX: cn base ratio is zero\n");
		ret = -1;
		जाओ error_ret;
	पूर्ण

	/* find the high and low priority frequencies */
	pbf_info->p1_high = 0;
	pbf_info->p1_low = ~0;

	pkg_id = get_physical_package_id(cpu);
	die_id = get_physical_die_id(cpu);

	क्रम (i = 0; i < topo_max_cpus; i++) अणु
		अगर (!CPU_ISSET_S(i, present_cpumask_size, present_cpumask))
			जारी;

		अगर (pkg_id != get_physical_package_id(i) ||
		    die_id != get_physical_die_id(i))
			जारी;

		CPU_SET_S(i, ctdp_level->core_cpumask_size,
			  ctdp_level->core_cpumask);

		cpu_bf = parse_पूर्णांक_file(1,
			"/sys/devices/system/cpu/cpu%d/cpufreq/base_frequency",
					i);
		अगर (cpu_bf > pbf_info->p1_high)
			pbf_info->p1_high = cpu_bf;
		अगर (cpu_bf < pbf_info->p1_low)
			pbf_info->p1_low = cpu_bf;
	पूर्ण

	अगर (pbf_info->p1_high == ~0UL) अणु
		debug_म_लिखो("CLX: maximum base frequency not set\n");
		ret = -1;
		जाओ error_ret;
	पूर्ण

	अगर (pbf_info->p1_low == 0) अणु
		debug_म_लिखो("CLX: minimum base frequency not set\n");
		ret = -1;
		जाओ error_ret;
	पूर्ण

	/* convert frequencies back to ratios */
	pbf_info->p1_high = pbf_info->p1_high / 100000;
	pbf_info->p1_low = pbf_info->p1_low / 100000;

	/* create high priority cpu mask */
	pbf_info->core_cpumask_size = alloc_cpu_set(&pbf_info->core_cpumask);
	क्रम (i = 0; i < topo_max_cpus; i++) अणु
		अगर (!CPU_ISSET_S(i, present_cpumask_size, present_cpumask))
			जारी;

		अगर (pkg_id != get_physical_package_id(i) ||
		    die_id != get_physical_die_id(i))
			जारी;

		cpu_bf = parse_पूर्णांक_file(1,
			"/sys/devices/system/cpu/cpu%d/cpufreq/base_frequency",
					i);
		cpu_bf = cpu_bf / 100000;
		अगर (cpu_bf == pbf_info->p1_high)
			CPU_SET_S(i, pbf_info->core_cpumask_size,
				  pbf_info->core_cpumask);
	पूर्ण

	/* extra ctdp & pbf काष्ठा parameters */
	ctdp_level->processed = 1;
	ctdp_level->pbf_support = 1; /* PBF is always supported and enabled */
	ctdp_level->pbf_enabled = 1;
	ctdp_level->fact_support = 0; /* FACT is never supported */
	ctdp_level->fact_enabled = 0;

	वापस 0;

error_ret:
	मुक्त_cpu_set(ctdp_level->core_cpumask);
	वापस ret;
पूर्ण

अटल व्योम dump_clx_n_config_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2,
				   व्योम *arg3, व्योम *arg4)
अणु
	पूर्णांक ret;

	अगर (tdp_level != 0xff && tdp_level != 0) अणु
		isst_display_error_info_message(1, "Invalid level", 1, tdp_level);
		निकास(0);
	पूर्ण

	ret = clx_n_config(cpu);
	अगर (ret) अणु
		debug_म_लिखो("clx_n_config failed");
	पूर्ण अन्यथा अणु
		काष्ठा isst_pkg_ctdp_level_info *ctdp_level;
		काष्ठा isst_pbf_info *pbf_info;

		ctdp_level = &clx_n_pkg_dev.ctdp_level[0];
		pbf_info = &ctdp_level->pbf_info;
		clx_n_pkg_dev.processed = 1;
		isst_ctdp_display_inक्रमmation(cpu, outf, tdp_level, &clx_n_pkg_dev);
		मुक्त_cpu_set(ctdp_level->core_cpumask);
		मुक्त_cpu_set(pbf_info->core_cpumask);
	पूर्ण
पूर्ण

अटल व्योम dump_isst_config_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2,
				     व्योम *arg3, व्योम *arg4)
अणु
	काष्ठा isst_pkg_ctdp pkg_dev;
	पूर्णांक ret;

	स_रखो(&pkg_dev, 0, माप(pkg_dev));
	ret = isst_get_process_ctdp(cpu, tdp_level, &pkg_dev);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Failed to get perf-profile info on cpu", 1, cpu);
		isst_ctdp_display_inक्रमmation_end(outf);
		निकास(1);
	पूर्ण अन्यथा अणु
		isst_ctdp_display_inक्रमmation(cpu, outf, tdp_level, &pkg_dev);
		isst_get_process_ctdp_complete(cpu, &pkg_dev);
	पूर्ण
पूर्ण

अटल व्योम dump_isst_config(पूर्णांक arg)
अणु
	व्योम *fn;

	अगर (cmd_help) अणु
		ख_लिखो(मानक_त्रुटि,
			"Print Intel(R) Speed Select Technology Performance profile configuration\n");
		ख_लिखो(मानक_त्रुटि,
			"including base frequency and turbo frequency configurations\n");
		ख_लिखो(मानक_त्रुटि, "Optional: -l|--level : Specify tdp level\n");
		ख_लिखो(मानक_त्रुटि,
			"\tIf no arguments, dump information for all TDP levels\n");
		निकास(0);
	पूर्ण

	अगर (!is_clx_n_platक्रमm())
		fn = dump_isst_config_क्रम_cpu;
	अन्यथा
		fn = dump_clx_n_config_क्रम_cpu;

	isst_ctdp_display_inक्रमmation_start(outf);

	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(fn, शून्य, शून्य, शून्य, शून्य);
	अन्यथा
		क्रम_each_online_package_in_set(fn, शून्य, शून्य, शून्य, शून्य);

	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल व्योम adjust_scaling_max_from_base_freq(पूर्णांक cpu);

अटल व्योम set_tdp_level_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
				  व्योम *arg4)
अणु
	पूर्णांक ret;

	ret = isst_set_tdp_level(cpu, tdp_level);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Set TDP level failed", 0, 0);
		isst_ctdp_display_inक्रमmation_end(outf);
		निकास(1);
	पूर्ण अन्यथा अणु
		isst_display_result(cpu, outf, "perf-profile", "set_tdp_level",
				    ret);
		अगर (क्रमce_online_offline) अणु
			काष्ठा isst_pkg_ctdp_level_info ctdp_level;
			पूर्णांक pkg_id = get_physical_package_id(cpu);
			पूर्णांक die_id = get_physical_die_id(cpu);

			/* Wait क्रम updated base frequencies */
			usleep(2000);

			ख_लिखो(मानक_त्रुटि, "Option is set to online/offline\n");
			ctdp_level.core_cpumask_size =
				alloc_cpu_set(&ctdp_level.core_cpumask);
			ret = isst_get_coremask_info(cpu, tdp_level, &ctdp_level);
			अगर (ret) अणु
				isst_display_error_info_message(1, "Can't get coremask, online/offline option is ignored", 0, 0);
				वापस;
			पूर्ण
			अगर (ctdp_level.cpu_count) अणु
				पूर्णांक i, max_cpus = get_topo_max_cpus();
				क्रम (i = 0; i < max_cpus; ++i) अणु
					अगर (pkg_id != get_physical_package_id(i) || die_id != get_physical_die_id(i))
						जारी;
					अगर (CPU_ISSET_S(i, ctdp_level.core_cpumask_size, ctdp_level.core_cpumask)) अणु
						ख_लिखो(मानक_त्रुटि, "online cpu %d\n", i);
						set_cpu_online_offline(i, 1);
						adjust_scaling_max_from_base_freq(i);
					पूर्ण अन्यथा अणु
						ख_लिखो(मानक_त्रुटि, "offline cpu %d\n", i);
						set_cpu_online_offline(i, 0);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम set_tdp_level(पूर्णांक arg)
अणु
	अगर (cmd_help) अणु
		ख_लिखो(मानक_त्रुटि, "Set Config TDP level\n");
		ख_लिखो(मानक_त्रुटि,
			"\t Arguments: -l|--level : Specify tdp level\n");
		ख_लिखो(मानक_त्रुटि,
			"\t Optional Arguments: -o | online : online/offline for the tdp level\n");
		ख_लिखो(मानक_त्रुटि,
			"\t  online/offline operation has limitations, refer to Linux hotplug documentation\n");
		निकास(0);
	पूर्ण

	अगर (tdp_level == 0xff) अणु
		isst_display_error_info_message(1, "Invalid command: specify tdp_level", 0, 0);
		निकास(1);
	पूर्ण
	isst_ctdp_display_inक्रमmation_start(outf);
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(set_tdp_level_क्रम_cpu, शून्य,
						  शून्य, शून्य, शून्य);
	अन्यथा
		क्रम_each_online_package_in_set(set_tdp_level_क्रम_cpu, शून्य,
					       शून्य, शून्य, शून्य);
	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल व्योम clx_n_dump_pbf_config_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2,
				       व्योम *arg3, व्योम *arg4)
अणु
	पूर्णांक ret;

	ret = clx_n_config(cpu);
	अगर (ret) अणु
		isst_display_error_info_message(1, "clx_n_config failed", 0, 0);
	पूर्ण अन्यथा अणु
		काष्ठा isst_pkg_ctdp_level_info *ctdp_level;
		काष्ठा isst_pbf_info *pbf_info;

		ctdp_level = &clx_n_pkg_dev.ctdp_level[0];
		pbf_info = &ctdp_level->pbf_info;
		isst_pbf_display_inक्रमmation(cpu, outf, tdp_level, pbf_info);
		मुक्त_cpu_set(ctdp_level->core_cpumask);
		मुक्त_cpu_set(pbf_info->core_cpumask);
	पूर्ण
पूर्ण

अटल व्योम dump_pbf_config_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
				    व्योम *arg4)
अणु
	काष्ठा isst_pbf_info pbf_info;
	पूर्णांक ret;

	ret = isst_get_pbf_info(cpu, tdp_level, &pbf_info);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Failed to get base-freq info at this level", 1, tdp_level);
		isst_ctdp_display_inक्रमmation_end(outf);
		निकास(1);
	पूर्ण अन्यथा अणु
		isst_pbf_display_inक्रमmation(cpu, outf, tdp_level, &pbf_info);
		isst_get_pbf_info_complete(&pbf_info);
	पूर्ण
पूर्ण

अटल व्योम dump_pbf_config(पूर्णांक arg)
अणु
	व्योम *fn;

	अगर (cmd_help) अणु
		ख_लिखो(मानक_त्रुटि,
			"Print Intel(R) Speed Select Technology base frequency configuration for a TDP level\n");
		ख_लिखो(मानक_त्रुटि,
			"\tArguments: -l|--level : Specify tdp level\n");
		निकास(0);
	पूर्ण

	अगर (tdp_level == 0xff) अणु
		isst_display_error_info_message(1, "Invalid command: specify tdp_level", 0, 0);
		निकास(1);
	पूर्ण

	अगर (!is_clx_n_platक्रमm())
		fn = dump_pbf_config_क्रम_cpu;
	अन्यथा
		fn = clx_n_dump_pbf_config_क्रम_cpu;

	isst_ctdp_display_inक्रमmation_start(outf);

	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(fn, शून्य, शून्य, शून्य, शून्य);
	अन्यथा
		क्रम_each_online_package_in_set(fn, शून्य, शून्य, शून्य, शून्य);

	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल पूर्णांक set_clos_param(पूर्णांक cpu, पूर्णांक clos, पूर्णांक epp, पूर्णांक wt, पूर्णांक min, पूर्णांक max)
अणु
	काष्ठा isst_clos_config clos_config;
	पूर्णांक ret;

	ret = isst_pm_get_clos(cpu, clos, &clos_config);
	अगर (ret) अणु
		isst_display_error_info_message(1, "isst_pm_get_clos failed", 0, 0);
		वापस ret;
	पूर्ण
	clos_config.clos_min = min;
	clos_config.clos_max = max;
	clos_config.epp = epp;
	clos_config.clos_prop_prio = wt;
	ret = isst_set_clos(cpu, clos, &clos_config);
	अगर (ret) अणु
		isst_display_error_info_message(1, "isst_set_clos failed", 0, 0);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_cpufreq_scaling_min_max(पूर्णांक cpu, पूर्णांक max, पूर्णांक freq)
अणु
	अक्षर buffer[128], freq_str[16];
	पूर्णांक fd, ret, len;

	अगर (max)
		snम_लिखो(buffer, माप(buffer),
			 "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_max_freq", cpu);
	अन्यथा
		snम_लिखो(buffer, माप(buffer),
			 "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_min_freq", cpu);

	fd = खोलो(buffer, O_WRONLY);
	अगर (fd < 0)
		वापस fd;

	snम_लिखो(freq_str, माप(freq_str), "%d", freq);
	len = म_माप(freq_str);
	ret = ग_लिखो(fd, freq_str, len);
	अगर (ret == -1) अणु
		बंद(fd);
		वापस ret;
	पूर्ण
	बंद(fd);

	वापस 0;
पूर्ण

अटल पूर्णांक no_turbo(व्योम)
अणु
	वापस parse_पूर्णांक_file(0, "/sys/devices/system/cpu/intel_pstate/no_turbo");
पूर्ण

अटल व्योम adjust_scaling_max_from_base_freq(पूर्णांक cpu)
अणु
	पूर्णांक base_freq, scaling_max_freq;

	scaling_max_freq = parse_पूर्णांक_file(0, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_max_freq", cpu);
	base_freq = get_cpufreq_base_freq(cpu);
	अगर (scaling_max_freq < base_freq || no_turbo())
		set_cpufreq_scaling_min_max(cpu, 1, base_freq);
पूर्ण

अटल व्योम adjust_scaling_min_from_base_freq(पूर्णांक cpu)
अणु
	पूर्णांक base_freq, scaling_min_freq;

	scaling_min_freq = parse_पूर्णांक_file(0, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_min_freq", cpu);
	base_freq = get_cpufreq_base_freq(cpu);
	अगर (scaling_min_freq < base_freq)
		set_cpufreq_scaling_min_max(cpu, 0, base_freq);
पूर्ण

अटल पूर्णांक set_clx_pbf_cpufreq_scaling_min_max(पूर्णांक cpu)
अणु
	काष्ठा isst_pkg_ctdp_level_info *ctdp_level;
	काष्ठा isst_pbf_info *pbf_info;
	पूर्णांक i, pkg_id, die_id, freq, freq_high, freq_low;
	पूर्णांक ret;

	ret = clx_n_config(cpu);
	अगर (ret) अणु
		debug_म_लिखो("cpufreq_scaling_min_max failed for CLX");
		वापस ret;
	पूर्ण

	ctdp_level = &clx_n_pkg_dev.ctdp_level[0];
	pbf_info = &ctdp_level->pbf_info;
	freq_high = pbf_info->p1_high * 100000;
	freq_low = pbf_info->p1_low * 100000;

	pkg_id = get_physical_package_id(cpu);
	die_id = get_physical_die_id(cpu);
	क्रम (i = 0; i < get_topo_max_cpus(); ++i) अणु
		अगर (pkg_id != get_physical_package_id(i) ||
		    die_id != get_physical_die_id(i))
			जारी;

		अगर (CPU_ISSET_S(i, pbf_info->core_cpumask_size,
				  pbf_info->core_cpumask))
			freq = freq_high;
		अन्यथा
			freq = freq_low;

		set_cpufreq_scaling_min_max(i, 1, freq);
		set_cpufreq_scaling_min_max(i, 0, freq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_cpufreq_scaling_min_max_from_cpuinfo(पूर्णांक cpu, पूर्णांक cpuinfo_max, पूर्णांक scaling_max)
अणु
	अक्षर buffer[128], min_freq[16];
	पूर्णांक fd, ret, len;

	अगर (!CPU_ISSET_S(cpu, present_cpumask_size, present_cpumask))
		वापस -1;

	अगर (cpuinfo_max)
		snम_लिखो(buffer, माप(buffer),
			 "/sys/devices/system/cpu/cpu%d/cpufreq/cpuinfo_max_freq", cpu);
	अन्यथा
		snम_लिखो(buffer, माप(buffer),
			 "/sys/devices/system/cpu/cpu%d/cpufreq/cpuinfo_min_freq", cpu);

	fd = खोलो(buffer, O_RDONLY);
	अगर (fd < 0)
		वापस fd;

	len = पढ़ो(fd, min_freq, माप(min_freq));
	बंद(fd);

	अगर (len < 0)
		वापस len;

	अगर (scaling_max)
		snम_लिखो(buffer, माप(buffer),
			 "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_max_freq", cpu);
	अन्यथा
		snम_लिखो(buffer, माप(buffer),
			 "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_min_freq", cpu);

	fd = खोलो(buffer, O_WRONLY);
	अगर (fd < 0)
		वापस fd;

	len = म_माप(min_freq);
	ret = ग_लिखो(fd, min_freq, len);
	अगर (ret == -1) अणु
		बंद(fd);
		वापस ret;
	पूर्ण
	बंद(fd);

	वापस 0;
पूर्ण

अटल व्योम set_scaling_min_to_cpuinfo_max(पूर्णांक cpu)
अणु
	पूर्णांक i, pkg_id, die_id;

	pkg_id = get_physical_package_id(cpu);
	die_id = get_physical_die_id(cpu);
	क्रम (i = 0; i < get_topo_max_cpus(); ++i) अणु
		अगर (pkg_id != get_physical_package_id(i) ||
		    die_id != get_physical_die_id(i))
			जारी;

		set_cpufreq_scaling_min_max_from_cpuinfo(i, 1, 0);
		adjust_scaling_min_from_base_freq(i);
	पूर्ण
पूर्ण

अटल व्योम set_scaling_min_to_cpuinfo_min(पूर्णांक cpu)
अणु
	पूर्णांक i, pkg_id, die_id;

	pkg_id = get_physical_package_id(cpu);
	die_id = get_physical_die_id(cpu);
	क्रम (i = 0; i < get_topo_max_cpus(); ++i) अणु
		अगर (pkg_id != get_physical_package_id(i) ||
		    die_id != get_physical_die_id(i))
			जारी;

		set_cpufreq_scaling_min_max_from_cpuinfo(i, 0, 0);
	पूर्ण
पूर्ण

अटल व्योम set_scaling_max_to_cpuinfo_max(पूर्णांक cpu)
अणु
	पूर्णांक i, pkg_id, die_id;

	pkg_id = get_physical_package_id(cpu);
	die_id = get_physical_die_id(cpu);
	क्रम (i = 0; i < get_topo_max_cpus(); ++i) अणु
		अगर (pkg_id != get_physical_package_id(i) ||
		    die_id != get_physical_die_id(i))
			जारी;

		set_cpufreq_scaling_min_max_from_cpuinfo(i, 1, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक set_core_priority_and_min(पूर्णांक cpu, पूर्णांक mask_size,
				     cpu_set_t *cpu_mask, पूर्णांक min_high,
				     पूर्णांक min_low)
अणु
	पूर्णांक pkg_id, die_id, ret, i;

	अगर (!CPU_COUNT_S(mask_size, cpu_mask))
		वापस -1;

	ret = set_clos_param(cpu, 0, 0, 0, min_high, 0xff);
	अगर (ret)
		वापस ret;

	ret = set_clos_param(cpu, 1, 15, 15, min_low, 0xff);
	अगर (ret)
		वापस ret;

	ret = set_clos_param(cpu, 2, 15, 15, min_low, 0xff);
	अगर (ret)
		वापस ret;

	ret = set_clos_param(cpu, 3, 15, 15, min_low, 0xff);
	अगर (ret)
		वापस ret;

	pkg_id = get_physical_package_id(cpu);
	die_id = get_physical_die_id(cpu);
	क्रम (i = 0; i < get_topo_max_cpus(); ++i) अणु
		पूर्णांक clos;

		अगर (pkg_id != get_physical_package_id(i) ||
		    die_id != get_physical_die_id(i))
			जारी;

		अगर (CPU_ISSET_S(i, mask_size, cpu_mask))
			clos = 0;
		अन्यथा
			clos = 3;

		debug_म_लिखो("Associate cpu: %d clos: %d\n", i, clos);
		ret = isst_clos_associate(i, clos);
		अगर (ret) अणु
			isst_display_error_info_message(1, "isst_clos_associate failed", 0, 0);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_pbf_core_घातer(पूर्णांक cpu)
अणु
	काष्ठा isst_pbf_info pbf_info;
	काष्ठा isst_pkg_ctdp pkg_dev;
	पूर्णांक ret;

	ret = isst_get_ctdp_levels(cpu, &pkg_dev);
	अगर (ret) अणु
		debug_म_लिखो("isst_get_ctdp_levels failed");
		वापस ret;
	पूर्ण
	debug_म_लिखो("Current_level: %d\n", pkg_dev.current_level);

	ret = isst_get_pbf_info(cpu, pkg_dev.current_level, &pbf_info);
	अगर (ret) अणु
		debug_म_लिखो("isst_get_pbf_info failed");
		वापस ret;
	पूर्ण
	debug_म_लिखो("p1_high: %d p1_low: %d\n", pbf_info.p1_high,
		     pbf_info.p1_low);

	ret = set_core_priority_and_min(cpu, pbf_info.core_cpumask_size,
					pbf_info.core_cpumask,
					pbf_info.p1_high, pbf_info.p1_low);
	अगर (ret) अणु
		debug_म_लिखो("set_core_priority_and_min failed");
		वापस ret;
	पूर्ण

	ret = isst_pm_qos_config(cpu, 1, 1);
	अगर (ret) अणु
		debug_म_लिखो("isst_pm_qos_config failed");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_pbf_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
			    व्योम *arg4)
अणु
	काष्ठा isst_pkg_ctdp_level_info ctdp_level;
	काष्ठा isst_pkg_ctdp pkg_dev;
	पूर्णांक ret;
	पूर्णांक status = *(पूर्णांक *)arg4;

	अगर (is_clx_n_platक्रमm()) अणु
		ret = 0;
		अगर (status) अणु
			set_clx_pbf_cpufreq_scaling_min_max(cpu);

		पूर्ण अन्यथा अणु
			set_scaling_max_to_cpuinfo_max(cpu);
			set_scaling_min_to_cpuinfo_min(cpu);
		पूर्ण
		जाओ disp_result;
	पूर्ण

	ret = isst_get_ctdp_levels(cpu, &pkg_dev);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Failed to get number of levels", 0, 0);
		जाओ disp_result;
	पूर्ण

	ret = isst_get_ctdp_control(cpu, pkg_dev.current_level, &ctdp_level);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Failed to get current level", 0, 0);
		जाओ disp_result;
	पूर्ण

	अगर (!ctdp_level.pbf_support) अणु
		isst_display_error_info_message(1, "base-freq feature is not present at this level", 1, pkg_dev.current_level);
		ret = -1;
		जाओ disp_result;
	पूर्ण

	अगर (स्वतः_mode && status) अणु
		ret = set_pbf_core_घातer(cpu);
		अगर (ret)
			जाओ disp_result;
	पूर्ण

	ret = isst_set_pbf_fact_status(cpu, 1, status);
	अगर (ret) अणु
		debug_म_लिखो("isst_set_pbf_fact_status failed");
		अगर (स्वतः_mode)
			isst_pm_qos_config(cpu, 0, 0);
	पूर्ण अन्यथा अणु
		अगर (स्वतः_mode) अणु
			अगर (status)
				set_scaling_min_to_cpuinfo_max(cpu);
			अन्यथा
				set_scaling_min_to_cpuinfo_min(cpu);
		पूर्ण
	पूर्ण

	अगर (स्वतः_mode && !status)
		isst_pm_qos_config(cpu, 0, 1);

disp_result:
	अगर (status)
		isst_display_result(cpu, outf, "base-freq", "enable",
				    ret);
	अन्यथा
		isst_display_result(cpu, outf, "base-freq", "disable",
				    ret);
पूर्ण

अटल व्योम set_pbf_enable(पूर्णांक arg)
अणु
	पूर्णांक enable = arg;

	अगर (cmd_help) अणु
		अगर (enable) अणु
			ख_लिखो(मानक_त्रुटि,
				"Enable Intel Speed Select Technology base frequency feature\n");
			अगर (is_clx_n_platक्रमm()) अणु
				ख_लिखो(मानक_त्रुटि,
					"\tOn this platform this command doesn't enable feature in the hardware.\n");
				ख_लिखो(मानक_त्रुटि,
					"\tIt updates the cpufreq scaling_min_freq to match cpufreq base_frequency.\n");
				निकास(0);

			पूर्ण
			ख_लिखो(मानक_त्रुटि,
				"\tOptional Arguments: -a|--auto : Use priority of cores to set core-power associations\n");
		पूर्ण अन्यथा अणु

			अगर (is_clx_n_platक्रमm()) अणु
				ख_लिखो(मानक_त्रुटि,
					"\tOn this platform this command doesn't disable feature in the hardware.\n");
				ख_लिखो(मानक_त्रुटि,
					"\tIt updates the cpufreq scaling_min_freq to match cpuinfo_min_freq\n");
				निकास(0);
			पूर्ण
			ख_लिखो(मानक_त्रुटि,
				"Disable Intel Speed Select Technology base frequency feature\n");
			ख_लिखो(मानक_त्रुटि,
				"\tOptional Arguments: -a|--auto : Also disable core-power associations\n");
		पूर्ण
		निकास(0);
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(set_pbf_क्रम_cpu, शून्य, शून्य,
						  शून्य, &enable);
	अन्यथा
		क्रम_each_online_package_in_set(set_pbf_क्रम_cpu, शून्य, शून्य,
					       शून्य, &enable);
	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल व्योम dump_fact_config_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2,
				     व्योम *arg3, व्योम *arg4)
अणु
	काष्ठा isst_fact_info fact_info;
	पूर्णांक ret;

	ret = isst_get_fact_info(cpu, tdp_level, fact_bucket, &fact_info);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Failed to get turbo-freq info at this level", 1, tdp_level);
		isst_ctdp_display_inक्रमmation_end(outf);
		निकास(1);
	पूर्ण अन्यथा अणु
		isst_fact_display_inक्रमmation(cpu, outf, tdp_level, fact_bucket,
					      fact_avx, &fact_info);
	पूर्ण
पूर्ण

अटल व्योम dump_fact_config(पूर्णांक arg)
अणु
	अगर (cmd_help) अणु
		ख_लिखो(मानक_त्रुटि,
			"Print complete Intel Speed Select Technology turbo frequency configuration for a TDP level. Other arguments are optional.\n");
		ख_लिखो(मानक_त्रुटि,
			"\tArguments: -l|--level : Specify tdp level\n");
		ख_लिखो(मानक_त्रुटि,
			"\tArguments: -b|--bucket : Bucket index to dump\n");
		ख_लिखो(मानक_त्रुटि,
			"\tArguments: -r|--trl-type : Specify trl type: sse|avx2|avx512\n");
		निकास(0);
	पूर्ण

	अगर (tdp_level == 0xff) अणु
		isst_display_error_info_message(1, "Invalid command: specify tdp_level\n", 0, 0);
		निकास(1);
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(dump_fact_config_क्रम_cpu,
						  शून्य, शून्य, शून्य, शून्य);
	अन्यथा
		क्रम_each_online_package_in_set(dump_fact_config_क्रम_cpu, शून्य,
					       शून्य, शून्य, शून्य);
	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल व्योम set_fact_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
			     व्योम *arg4)
अणु
	काष्ठा isst_pkg_ctdp_level_info ctdp_level;
	काष्ठा isst_pkg_ctdp pkg_dev;
	पूर्णांक ret;
	पूर्णांक status = *(पूर्णांक *)arg4;

	ret = isst_get_ctdp_levels(cpu, &pkg_dev);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Failed to get number of levels", 0, 0);
		जाओ disp_results;
	पूर्ण

	ret = isst_get_ctdp_control(cpu, pkg_dev.current_level, &ctdp_level);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Failed to get current level", 0, 0);
		जाओ disp_results;
	पूर्ण

	अगर (!ctdp_level.fact_support) अणु
		isst_display_error_info_message(1, "turbo-freq feature is not present at this level", 1, pkg_dev.current_level);
		ret = -1;
		जाओ disp_results;
	पूर्ण

	अगर (status) अणु
		ret = isst_pm_qos_config(cpu, 1, 1);
		अगर (ret)
			जाओ disp_results;
	पूर्ण

	ret = isst_set_pbf_fact_status(cpu, 0, status);
	अगर (ret) अणु
		debug_म_लिखो("isst_set_pbf_fact_status failed");
		अगर (स्वतः_mode)
			isst_pm_qos_config(cpu, 0, 0);

		जाओ disp_results;
	पूर्ण

	/* Set TRL */
	अगर (status) अणु
		काष्ठा isst_pkg_ctdp pkg_dev;

		ret = isst_get_ctdp_levels(cpu, &pkg_dev);
		अगर (!ret)
			ret = isst_set_trl(cpu, fact_trl);
		अगर (ret && स्वतः_mode)
			isst_pm_qos_config(cpu, 0, 0);
	पूर्ण अन्यथा अणु
		अगर (स्वतः_mode)
			isst_pm_qos_config(cpu, 0, 0);
	पूर्ण

disp_results:
	अगर (status) अणु
		isst_display_result(cpu, outf, "turbo-freq", "enable", ret);
		अगर (ret)
			fact_enable_fail = ret;
	पूर्ण अन्यथा अणु
		/* Since we modअगरied TRL during Fact enable, restore it */
		isst_set_trl_from_current_tdp(cpu, fact_trl);
		isst_display_result(cpu, outf, "turbo-freq", "disable", ret);
	पूर्ण
पूर्ण

अटल व्योम set_fact_enable(पूर्णांक arg)
अणु
	पूर्णांक i, ret, enable = arg;

	अगर (cmd_help) अणु
		अगर (enable) अणु
			ख_लिखो(मानक_त्रुटि,
				"Enable Intel Speed Select Technology Turbo frequency feature\n");
			ख_लिखो(मानक_त्रुटि,
				"Optional: -t|--trl : Specify turbo ratio limit\n");
			ख_लिखो(मानक_त्रुटि,
				"\tOptional Arguments: -a|--auto : Designate specified target CPUs with");
			ख_लिखो(मानक_त्रुटि,
				"-C|--cpu option as as high priority using core-power feature\n");
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि,
				"Disable Intel Speed Select Technology turbo frequency feature\n");
			ख_लिखो(मानक_त्रुटि,
				"Optional: -t|--trl : Specify turbo ratio limit\n");
			ख_लिखो(मानक_त्रुटि,
				"\tOptional Arguments: -a|--auto : Also disable core-power associations\n");
		पूर्ण
		निकास(0);
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(set_fact_क्रम_cpu, शून्य, शून्य,
						  शून्य, &enable);
	अन्यथा
		क्रम_each_online_package_in_set(set_fact_क्रम_cpu, शून्य, शून्य,
					       शून्य, &enable);
	isst_ctdp_display_inक्रमmation_end(outf);

	अगर (!fact_enable_fail && enable && स्वतः_mode) अणु
		/*
		 * When we adjust CLOS param, we have to set क्रम siblings also.
		 * So क्रम the each user specअगरied CPU, also add the sibling
		 * in the present_cpu_mask.
		 */
		क्रम (i = 0; i < get_topo_max_cpus(); ++i) अणु
			अक्षर buffer[128], sibling_list[128], *cpu_str;
			पूर्णांक fd, len;

			अगर (!CPU_ISSET_S(i, target_cpumask_size, target_cpumask))
				जारी;

			snम_लिखो(buffer, माप(buffer),
				 "/sys/devices/system/cpu/cpu%d/topology/thread_siblings_list", i);

			fd = खोलो(buffer, O_RDONLY);
			अगर (fd < 0)
				जारी;

			len = पढ़ो(fd, sibling_list, माप(sibling_list));
			बंद(fd);

			अगर (len < 0)
				जारी;

			cpu_str = म_मोहर(sibling_list, ",");
			जबतक (cpu_str != शून्य) अणु
				पूर्णांक cpu;

				माला_पूछो(cpu_str, "%d", &cpu);
				CPU_SET_S(cpu, target_cpumask_size, target_cpumask);
				cpu_str = म_मोहर(शून्य, ",");
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < get_topo_max_cpus(); ++i) अणु
			पूर्णांक clos;

			अगर (!CPU_ISSET_S(i, present_cpumask_size, present_cpumask))
				जारी;

			ret = set_clos_param(i, 0, 0, 0, 0, 0xff);
			अगर (ret)
				जाओ error_disp;

			ret = set_clos_param(i, 1, 15, 15, 0, 0xff);
			अगर (ret)
				जाओ error_disp;

			ret = set_clos_param(i, 2, 15, 15, 0, 0xff);
			अगर (ret)
				जाओ error_disp;

			ret = set_clos_param(i, 3, 15, 15, 0, 0xff);
			अगर (ret)
				जाओ error_disp;

			अगर (CPU_ISSET_S(i, target_cpumask_size, target_cpumask))
				clos = 0;
			अन्यथा
				clos = 3;

			debug_म_लिखो("Associate cpu: %d clos: %d\n", i, clos);
			ret = isst_clos_associate(i, clos);
			अगर (ret)
				जाओ error_disp;
		पूर्ण
		isst_display_result(-1, outf, "turbo-freq --auto", "enable", 0);
	पूर्ण

	वापस;

error_disp:
	isst_display_result(i, outf, "turbo-freq --auto", "enable", ret);

पूर्ण

अटल व्योम enable_clos_qos_config(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
				   व्योम *arg4)
अणु
	पूर्णांक ret;
	पूर्णांक status = *(पूर्णांक *)arg4;

	अगर (is_skx_based_platक्रमm())
		clos_priority_type = 1;

	ret = isst_pm_qos_config(cpu, status, clos_priority_type);
	अगर (ret)
		isst_display_error_info_message(1, "isst_pm_qos_config failed", 0, 0);

	अगर (status)
		isst_display_result(cpu, outf, "core-power", "enable",
				    ret);
	अन्यथा
		isst_display_result(cpu, outf, "core-power", "disable",
				    ret);
पूर्ण

अटल व्योम set_clos_enable(पूर्णांक arg)
अणु
	पूर्णांक enable = arg;

	अगर (cmd_help) अणु
		अगर (enable) अणु
			ख_लिखो(मानक_त्रुटि,
				"Enable core-power for a package/die\n");
			अगर (!is_skx_based_platक्रमm()) अणु
				ख_लिखो(मानक_त्रुटि,
					"\tClos Enable: Specify priority type with [--priority|-p]\n");
				ख_लिखो(मानक_त्रुटि, "\t\t 0: Proportional, 1: Ordered\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि,
				"Disable core-power: [No command arguments are required]\n");
		पूर्ण
		निकास(0);
	पूर्ण

	अगर (enable && cpufreq_sysfs_present()) अणु
		ख_लिखो(मानक_त्रुटि,
			"cpufreq subsystem and core-power enable will interfere with each other!\n");
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(enable_clos_qos_config, शून्य,
						  शून्य, शून्य, &enable);
	अन्यथा
		क्रम_each_online_package_in_set(enable_clos_qos_config, शून्य,
					       शून्य, शून्य, &enable);
	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल व्योम dump_clos_config_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2,
				     व्योम *arg3, व्योम *arg4)
अणु
	काष्ठा isst_clos_config clos_config;
	पूर्णांक ret;

	ret = isst_pm_get_clos(cpu, current_clos, &clos_config);
	अगर (ret)
		isst_display_error_info_message(1, "isst_pm_get_clos failed", 0, 0);
	अन्यथा
		isst_clos_display_inक्रमmation(cpu, outf, current_clos,
					      &clos_config);
पूर्ण

अटल व्योम dump_clos_config(पूर्णांक arg)
अणु
	अगर (cmd_help) अणु
		ख_लिखो(मानक_त्रुटि,
			"Print Intel Speed Select Technology core power configuration\n");
		ख_लिखो(मानक_त्रुटि,
			"\tArguments: [-c | --clos]: Specify clos id\n");
		निकास(0);
	पूर्ण
	अगर (current_clos < 0 || current_clos > 3) अणु
		isst_display_error_info_message(1, "Invalid clos id\n", 0, 0);
		isst_ctdp_display_inक्रमmation_end(outf);
		निकास(0);
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(dump_clos_config_क्रम_cpu,
						  शून्य, शून्य, शून्य, शून्य);
	अन्यथा
		क्रम_each_online_package_in_set(dump_clos_config_क्रम_cpu, शून्य,
					       शून्य, शून्य, शून्य);
	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल व्योम get_clos_info_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
				  व्योम *arg4)
अणु
	पूर्णांक enable, ret, prio_type;

	ret = isst_clos_get_clos_inक्रमmation(cpu, &enable, &prio_type);
	अगर (ret)
		isst_display_error_info_message(1, "isst_clos_get_info failed", 0, 0);
	अन्यथा अणु
		पूर्णांक cp_state, cp_cap;

		isst_पढ़ो_pm_config(cpu, &cp_state, &cp_cap);
		isst_clos_display_clos_inक्रमmation(cpu, outf, enable, prio_type,
						   cp_state, cp_cap);
	पूर्ण
पूर्ण

अटल व्योम dump_clos_info(पूर्णांक arg)
अणु
	अगर (cmd_help) अणु
		ख_लिखो(मानक_त्रुटि,
			"Print Intel Speed Select Technology core power information\n");
		ख_लिखो(मानक_त्रुटि, "\t Optionally specify targeted cpu id with [--cpu|-c]\n");
		निकास(0);
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(get_clos_info_क्रम_cpu, शून्य,
						  शून्य, शून्य, शून्य);
	अन्यथा
		क्रम_each_online_package_in_set(get_clos_info_क्रम_cpu, शून्य,
					       शून्य, शून्य, शून्य);
	isst_ctdp_display_inक्रमmation_end(outf);

पूर्ण

अटल व्योम set_clos_config_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
				    व्योम *arg4)
अणु
	काष्ठा isst_clos_config clos_config;
	पूर्णांक ret;

	clos_config.pkg_id = get_physical_package_id(cpu);
	clos_config.die_id = get_physical_die_id(cpu);

	clos_config.epp = clos_epp;
	clos_config.clos_prop_prio = clos_prop_prio;
	clos_config.clos_min = clos_min;
	clos_config.clos_max = clos_max;
	clos_config.clos_desired = clos_desired;
	ret = isst_set_clos(cpu, current_clos, &clos_config);
	अगर (ret)
		isst_display_error_info_message(1, "isst_set_clos failed", 0, 0);
	अन्यथा
		isst_display_result(cpu, outf, "core-power", "config", ret);
पूर्ण

अटल व्योम set_clos_config(पूर्णांक arg)
अणु
	अगर (cmd_help) अणु
		ख_लिखो(मानक_त्रुटि,
			"Set core-power configuration for one of the four clos ids\n");
		ख_लिखो(मानक_त्रुटि,
			"\tSpecify targeted clos id with [--clos|-c]\n");
		अगर (!is_skx_based_platक्रमm()) अणु
			ख_लिखो(मानक_त्रुटि, "\tSpecify clos EPP with [--epp|-e]\n");
			ख_लिखो(मानक_त्रुटि,
				"\tSpecify clos Proportional Priority [--weight|-w]\n");
		पूर्ण
		ख_लिखो(मानक_त्रुटि, "\tSpecify clos min in MHz with [--min|-n]\n");
		ख_लिखो(मानक_त्रुटि, "\tSpecify clos max in MHz with [--max|-m]\n");
		निकास(0);
	पूर्ण

	अगर (current_clos < 0 || current_clos > 3) अणु
		isst_display_error_info_message(1, "Invalid clos id\n", 0, 0);
		निकास(0);
	पूर्ण
	अगर (!is_skx_based_platक्रमm() && (clos_epp < 0 || clos_epp > 0x0F)) अणु
		ख_लिखो(मानक_त्रुटि, "clos epp is not specified or invalid, default: 0\n");
		clos_epp = 0;
	पूर्ण
	अगर (!is_skx_based_platक्रमm() && (clos_prop_prio < 0 || clos_prop_prio > 0x0F)) अणु
		ख_लिखो(मानक_त्रुटि,
			"clos frequency weight is not specified or invalid, default: 0\n");
		clos_prop_prio = 0;
	पूर्ण
	अगर (clos_min < 0) अणु
		ख_लिखो(मानक_त्रुटि, "clos min is not specified, default: 0\n");
		clos_min = 0;
	पूर्ण
	अगर (clos_max < 0) अणु
		ख_लिखो(मानक_त्रुटि, "clos max is not specified, default: Max frequency (ratio 0xff)\n");
		clos_max = 0xff;
	पूर्ण
	अगर (clos_desired) अणु
		ख_लिखो(मानक_त्रुटि, "clos desired is not supported on this platform\n");
		clos_desired = 0x00;
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(set_clos_config_क्रम_cpu, शून्य,
						  शून्य, शून्य, शून्य);
	अन्यथा
		क्रम_each_online_package_in_set(set_clos_config_क्रम_cpu, शून्य,
					       शून्य, शून्य, शून्य);
	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल व्योम set_clos_assoc_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
				   व्योम *arg4)
अणु
	पूर्णांक ret;

	ret = isst_clos_associate(cpu, current_clos);
	अगर (ret)
		debug_म_लिखो("isst_clos_associate failed");
	अन्यथा
		isst_display_result(cpu, outf, "core-power", "assoc", ret);
पूर्ण

अटल व्योम set_clos_assoc(पूर्णांक arg)
अणु
	अगर (cmd_help) अणु
		ख_लिखो(मानक_त्रुटि, "Associate a clos id to a CPU\n");
		ख_लिखो(मानक_त्रुटि,
			"\tSpecify targeted clos id with [--clos|-c]\n");
		ख_लिखो(मानक_त्रुटि,
			"\tFor example to associate clos 1 to CPU 0: issue\n");
		ख_लिखो(मानक_त्रुटि,
			"\tintel-speed-select --cpu 0 core-power assoc --clos 1\n");
		निकास(0);
	पूर्ण

	अगर (current_clos < 0 || current_clos > 3) अणु
		isst_display_error_info_message(1, "Invalid clos id\n", 0, 0);
		निकास(0);
	पूर्ण
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(set_clos_assoc_क्रम_cpu, शून्य,
						  शून्य, शून्य, शून्य);
	अन्यथा अणु
		isst_display_error_info_message(1, "Invalid target cpu. Specify with [-c|--cpu]", 0, 0);
	पूर्ण
पूर्ण

अटल व्योम get_clos_assoc_क्रम_cpu(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
				   व्योम *arg4)
अणु
	पूर्णांक clos, ret;

	ret = isst_clos_get_assoc_status(cpu, &clos);
	अगर (ret)
		isst_display_error_info_message(1, "isst_clos_get_assoc_status failed", 0, 0);
	अन्यथा
		isst_clos_display_assoc_inक्रमmation(cpu, outf, clos);
पूर्ण

अटल व्योम get_clos_assoc(पूर्णांक arg)
अणु
	अगर (cmd_help) अणु
		ख_लिखो(मानक_त्रुटि, "Get associate clos id to a CPU\n");
		ख_लिखो(मानक_त्रुटि, "\tSpecify targeted cpu id with [--cpu|-c]\n");
		निकास(0);
	पूर्ण

	अगर (!max_target_cpus) अणु
		isst_display_error_info_message(1, "Invalid target cpu. Specify with [-c|--cpu]", 0, 0);
		निकास(0);
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);
	क्रम_each_online_target_cpu_in_set(get_clos_assoc_क्रम_cpu, शून्य,
					  शून्य, शून्य, शून्य);
	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल व्योम set_turbo_mode_क्रम_cpu(पूर्णांक cpu, पूर्णांक status)
अणु
	पूर्णांक base_freq;

	अगर (status) अणु
		base_freq = get_cpufreq_base_freq(cpu);
		set_cpufreq_scaling_min_max(cpu, 1, base_freq);
	पूर्ण अन्यथा अणु
		set_scaling_max_to_cpuinfo_max(cpu);
	पूर्ण

	अगर (status) अणु
		isst_display_result(cpu, outf, "turbo-mode", "enable", 0);
	पूर्ण अन्यथा अणु
		isst_display_result(cpu, outf, "turbo-mode", "disable", 0);
	पूर्ण
पूर्ण

अटल व्योम set_turbo_mode(पूर्णांक arg)
अणु
	पूर्णांक i, enable = arg;

	अगर (cmd_help) अणु
		अगर (enable)
			ख_लिखो(मानक_त्रुटि, "Set turbo mode enable\n");
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "Set turbo mode disable\n");
		निकास(0);
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);

	क्रम (i = 0; i < topo_max_cpus; ++i) अणु
		पूर्णांक online;

		अगर (i)
			online = parse_पूर्णांक_file(
				1, "/sys/devices/system/cpu/cpu%d/online", i);
		अन्यथा
			online =
				1; /* online entry क्रम CPU 0 needs some special configs */

		अगर (online)
			set_turbo_mode_क्रम_cpu(i, enable);

	पूर्ण
	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल व्योम get_set_trl(पूर्णांक cpu, व्योम *arg1, व्योम *arg2, व्योम *arg3,
			व्योम *arg4)
अणु
	अचिन्हित दीर्घ दीर्घ trl;
	पूर्णांक set = *(पूर्णांक *)arg4;
	पूर्णांक ret;

	अगर (set && !fact_trl) अणु
		isst_display_error_info_message(1, "Invalid TRL. Specify with [-t|--trl]", 0, 0);
		निकास(0);
	पूर्ण

	अगर (set) अणु
		ret = isst_set_trl(cpu, fact_trl);
		isst_display_result(cpu, outf, "turbo-mode", "set-trl", ret);
		वापस;
	पूर्ण

	ret = isst_get_trl(cpu, &trl);
	अगर (ret)
		isst_display_result(cpu, outf, "turbo-mode", "get-trl", ret);
	अन्यथा
		isst_trl_display_inक्रमmation(cpu, outf, trl);
पूर्ण

अटल व्योम process_trl(पूर्णांक arg)
अणु
	अगर (cmd_help) अणु
		अगर (arg) अणु
			ख_लिखो(मानक_त्रुटि, "Set TRL (turbo ratio limits)\n");
			ख_लिखो(मानक_त्रुटि, "\t t|--trl: Specify turbo ratio limit for setting TRL\n");
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "Get TRL (turbo ratio limits)\n");
		पूर्ण
		निकास(0);
	पूर्ण

	isst_ctdp_display_inक्रमmation_start(outf);
	अगर (max_target_cpus)
		क्रम_each_online_target_cpu_in_set(get_set_trl, शून्य,
						  शून्य, शून्य, &arg);
	अन्यथा
		क्रम_each_online_package_in_set(get_set_trl, शून्य,
					       शून्य, शून्य, &arg);
	isst_ctdp_display_inक्रमmation_end(outf);
पूर्ण

अटल काष्ठा process_cmd_काष्ठा clx_n_cmds[] = अणु
	अणु "perf-profile", "info", dump_isst_config, 0 पूर्ण,
	अणु "base-freq", "info", dump_pbf_config, 0 पूर्ण,
	अणु "base-freq", "enable", set_pbf_enable, 1 पूर्ण,
	अणु "base-freq", "disable", set_pbf_enable, 0 पूर्ण,
	अणु शून्य, शून्य, शून्य, 0 पूर्ण
पूर्ण;

अटल काष्ठा process_cmd_काष्ठा isst_cmds[] = अणु
	अणु "perf-profile", "get-lock-status", get_tdp_locked, 0 पूर्ण,
	अणु "perf-profile", "get-config-levels", get_tdp_levels, 0 पूर्ण,
	अणु "perf-profile", "get-config-version", get_tdp_version, 0 पूर्ण,
	अणु "perf-profile", "get-config-enabled", get_tdp_enabled, 0 पूर्ण,
	अणु "perf-profile", "get-config-current-level", get_tdp_current_level,
	 0 पूर्ण,
	अणु "perf-profile", "set-config-level", set_tdp_level, 0 पूर्ण,
	अणु "perf-profile", "info", dump_isst_config, 0 पूर्ण,
	अणु "base-freq", "info", dump_pbf_config, 0 पूर्ण,
	अणु "base-freq", "enable", set_pbf_enable, 1 पूर्ण,
	अणु "base-freq", "disable", set_pbf_enable, 0 पूर्ण,
	अणु "turbo-freq", "info", dump_fact_config, 0 पूर्ण,
	अणु "turbo-freq", "enable", set_fact_enable, 1 पूर्ण,
	अणु "turbo-freq", "disable", set_fact_enable, 0 पूर्ण,
	अणु "core-power", "info", dump_clos_info, 0 पूर्ण,
	अणु "core-power", "enable", set_clos_enable, 1 पूर्ण,
	अणु "core-power", "disable", set_clos_enable, 0 पूर्ण,
	अणु "core-power", "config", set_clos_config, 0 पूर्ण,
	अणु "core-power", "get-config", dump_clos_config, 0 पूर्ण,
	अणु "core-power", "assoc", set_clos_assoc, 0 पूर्ण,
	अणु "core-power", "get-assoc", get_clos_assoc, 0 पूर्ण,
	अणु "turbo-mode", "enable", set_turbo_mode, 0 पूर्ण,
	अणु "turbo-mode", "disable", set_turbo_mode, 1 पूर्ण,
	अणु "turbo-mode", "get-trl", process_trl, 0 पूर्ण,
	अणु "turbo-mode", "set-trl", process_trl, 1 पूर्ण,
	अणु शून्य, शून्य, शून्य पूर्ण
पूर्ण;

/*
 * parse cpuset with following syntax
 * 1,2,4..6,8-10 and set bits in cpu_subset
 */
व्योम parse_cpu_command(अक्षर *optarg)
अणु
	अचिन्हित पूर्णांक start, end;
	अक्षर *next;

	next = optarg;

	जबतक (next && *next) अणु
		अगर (*next == '-') /* no negative cpu numbers */
			जाओ error;

		start = म_से_अदीर्घ(next, &next, 10);

		अगर (max_target_cpus < MAX_CPUS_IN_ONE_REQ)
			target_cpus[max_target_cpus++] = start;

		अगर (*next == '\0')
			अवरोध;

		अगर (*next == ',') अणु
			next += 1;
			जारी;
		पूर्ण

		अगर (*next == '-') अणु
			next += 1; /* start range */
		पूर्ण अन्यथा अगर (*next == '.') अणु
			next += 1;
			अगर (*next == '.')
				next += 1; /* start range */
			अन्यथा
				जाओ error;
		पूर्ण

		end = म_से_अदीर्घ(next, &next, 10);
		अगर (end <= start)
			जाओ error;

		जबतक (++start <= end) अणु
			अगर (max_target_cpus < MAX_CPUS_IN_ONE_REQ)
				target_cpus[max_target_cpus++] = start;
		पूर्ण

		अगर (*next == ',')
			next += 1;
		अन्यथा अगर (*next != '\0')
			जाओ error;
	पूर्ण

#अगर_घोषित DEBUG
	अणु
		पूर्णांक i;

		क्रम (i = 0; i < max_target_cpus; ++i)
			म_लिखो("cpu [%d] in arg\n", target_cpus[i]);
	पूर्ण
#पूर्ण_अगर
	वापस;

error:
	ख_लिखो(मानक_त्रुटि, "\"--cpu %s\" malformed\n", optarg);
	निकास(-1);
पूर्ण

अटल व्योम parse_cmd_args(पूर्णांक argc, पूर्णांक start, अक्षर **argv)
अणु
	पूर्णांक opt;
	पूर्णांक option_index;

	अटल काष्ठा option दीर्घ_options[] = अणु
		अणु "bucket", required_argument, 0, 'b' पूर्ण,
		अणु "level", required_argument, 0, 'l' पूर्ण,
		अणु "online", required_argument, 0, 'o' पूर्ण,
		अणु "trl-type", required_argument, 0, 'r' पूर्ण,
		अणु "trl", required_argument, 0, 't' पूर्ण,
		अणु "help", no_argument, 0, 'h' पूर्ण,
		अणु "clos", required_argument, 0, 'c' पूर्ण,
		अणु "desired", required_argument, 0, 'd' पूर्ण,
		अणु "epp", required_argument, 0, 'e' पूर्ण,
		अणु "min", required_argument, 0, 'n' पूर्ण,
		अणु "max", required_argument, 0, 'm' पूर्ण,
		अणु "priority", required_argument, 0, 'p' पूर्ण,
		अणु "weight", required_argument, 0, 'w' पूर्ण,
		अणु "auto", no_argument, 0, 'a' पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;

	option_index = start;

	optind = start + 1;
	जबतक ((opt = getopt_दीर्घ(argc, argv, "b:l:t:c:d:e:n:m:p:w:r:hoa",
				  दीर्घ_options, &option_index)) != -1) अणु
		चयन (opt) अणु
		हाल 'a':
			स्वतः_mode = 1;
			अवरोध;
		हाल 'b':
			fact_bucket = म_से_प(optarg);
			अवरोध;
		हाल 'h':
			cmd_help = 1;
			अवरोध;
		हाल 'l':
			tdp_level = म_से_प(optarg);
			अवरोध;
		हाल 'o':
			क्रमce_online_offline = 1;
			अवरोध;
		हाल 't':
			माला_पूछो(optarg, "0x%llx", &fact_trl);
			अवरोध;
		हाल 'r':
			अगर (!म_भेदन(optarg, "sse", 3)) अणु
				fact_avx = 0x01;
			पूर्ण अन्यथा अगर (!म_भेदन(optarg, "avx2", 4)) अणु
				fact_avx = 0x02;
			पूर्ण अन्यथा अगर (!म_भेदन(optarg, "avx512", 6)) अणु
				fact_avx = 0x04;
			पूर्ण अन्यथा अणु
				ख_लिखो(outf, "Invalid sse,avx options\n");
				निकास(1);
			पूर्ण
			अवरोध;
		/* CLOS related */
		हाल 'c':
			current_clos = म_से_प(optarg);
			अवरोध;
		हाल 'd':
			clos_desired = म_से_प(optarg);
			clos_desired /= DISP_FREQ_MULTIPLIER;
			अवरोध;
		हाल 'e':
			clos_epp = म_से_प(optarg);
			अगर (is_skx_based_platक्रमm()) अणु
				isst_display_error_info_message(1, "epp can't be specified on this platform", 0, 0);
				निकास(0);
			पूर्ण
			अवरोध;
		हाल 'n':
			clos_min = म_से_प(optarg);
			clos_min /= DISP_FREQ_MULTIPLIER;
			अवरोध;
		हाल 'm':
			clos_max = म_से_प(optarg);
			clos_max /= DISP_FREQ_MULTIPLIER;
			अवरोध;
		हाल 'p':
			clos_priority_type = म_से_प(optarg);
			अगर (is_skx_based_platक्रमm() && !clos_priority_type) अणु
				isst_display_error_info_message(1, "Invalid clos priority type: proportional for this platform", 0, 0);
				निकास(0);
			पूर्ण
			अवरोध;
		हाल 'w':
			clos_prop_prio = म_से_प(optarg);
			अगर (is_skx_based_platक्रमm()) अणु
				isst_display_error_info_message(1, "weight can't be specified on this platform", 0, 0);
				निकास(0);
			पूर्ण
			अवरोध;
		शेष:
			म_लिखो("Unknown option: ignore\n");
		पूर्ण
	पूर्ण

	अगर (argv[optind])
		म_लिखो("Garbage at the end of command: ignore\n");
पूर्ण

अटल व्योम isst_help(व्योम)
अणु
	म_लिखो("perf-profile:\टAn architectural mechanism that allows multiple optimized \न\
		perक्रमmance profiles per प्रणाली via अटल and/or dynamic\न\
		adjusपंचांगent of core count, workload, Tjmax, and\न\
		TDP, etc.\न");
	म_लिखो("\nCommands : For feature=perf-profile\n");
	म_लिखो("\tinfo\n");

	अगर (!is_clx_n_platक्रमm()) अणु
		म_लिखो("\tget-lock-status\n");
		म_लिखो("\tget-config-levels\n");
		म_लिखो("\tget-config-version\n");
		म_लिखो("\tget-config-enabled\n");
		म_लिखो("\tget-config-current-level\n");
		म_लिखो("\tset-config-level\n");
	पूर्ण
पूर्ण

अटल व्योम pbf_help(व्योम)
अणु
	म_लिखो("base-freq:\टEnables users to increase guaranteed base frequency\न\
		on certain cores (high priority cores) in exchange क्रम lower\न\
		base frequency on reमुख्यing cores (low priority cores).\न");
	म_लिखो("\tcommand : info\n");
	म_लिखो("\tcommand : enable\n");
	म_लिखो("\tcommand : disable\n");
पूर्ण

अटल व्योम fact_help(व्योम)
अणु
	म_लिखो("turbo-freq:\टEnables the ability to set dअगरferent turbo ratio\न\
		limits to cores based on priority.\न");
	म_लिखो("\nCommand: For feature=turbo-freq\n");
	म_लिखो("\tcommand : info\n");
	म_लिखो("\tcommand : enable\n");
	म_लिखो("\tcommand : disable\n");
पूर्ण

अटल व्योम turbo_mode_help(व्योम)
अणु
	म_लिखो("turbo-mode:\tEnables users to enable/disable turbo mode by adjusting frequency settings. Also allows to get and set turbo ratio limits (TRL).\n");
	म_लिखो("\tcommand : enable\n");
	म_लिखो("\tcommand : disable\n");
	म_लिखो("\tcommand : get-trl\n");
	म_लिखो("\tcommand : set-trl\n");
पूर्ण


अटल व्योम core_घातer_help(व्योम)
अणु
	म_लिखो("core-घातer:\टInterface that allows user to define per core/tile\न\
		priority.\न");
	म_लिखो("\nCommands : For feature=core-power\n");
	म_लिखो("\tinfo\n");
	म_लिखो("\tenable\n");
	म_लिखो("\tdisable\n");
	म_लिखो("\tconfig\n");
	म_लिखो("\tget-config\n");
	म_लिखो("\tassoc\n");
	म_लिखो("\tget-assoc\n");
पूर्ण

काष्ठा process_cmd_help_काष्ठा अणु
	अक्षर *feature;
	व्योम (*process_fn)(व्योम);
पूर्ण;

अटल काष्ठा process_cmd_help_काष्ठा isst_help_cmds[] = अणु
	अणु "perf-profile", isst_help पूर्ण,
	अणु "base-freq", pbf_help पूर्ण,
	अणु "turbo-freq", fact_help पूर्ण,
	अणु "core-power", core_घातer_help पूर्ण,
	अणु "turbo-mode", turbo_mode_help पूर्ण,
	अणु शून्य, शून्य पूर्ण
पूर्ण;

अटल काष्ठा process_cmd_help_काष्ठा clx_n_help_cmds[] = अणु
	अणु "perf-profile", isst_help पूर्ण,
	अणु "base-freq", pbf_help पूर्ण,
	अणु शून्य, शून्य पूर्ण
पूर्ण;

व्योम process_command(पूर्णांक argc, अक्षर **argv,
		     काष्ठा process_cmd_help_काष्ठा *help_cmds,
		     काष्ठा process_cmd_काष्ठा *cmds)
अणु
	पूर्णांक i = 0, matched = 0;
	अक्षर *feature = argv[optind];
	अक्षर *cmd = argv[optind + 1];

	अगर (!feature || !cmd)
		वापस;

	debug_म_लिखो("feature name [%s] command [%s]\n", feature, cmd);
	अगर (!म_भेद(cmd, "-h") || !म_भेद(cmd, "--help")) अणु
		जबतक (help_cmds[i].feature) अणु
			अगर (!म_भेद(help_cmds[i].feature, feature)) अणु
				help_cmds[i].process_fn();
				निकास(0);
			पूर्ण
			++i;
		पूर्ण
	पूर्ण

	अगर (!is_clx_n_platक्रमm())
		create_cpu_map();

	i = 0;
	जबतक (cmds[i].feature) अणु
		अगर (!म_भेद(cmds[i].feature, feature) &&
		    !म_भेद(cmds[i].command, cmd)) अणु
			parse_cmd_args(argc, optind + 1, argv);
			cmds[i].process_fn(cmds[i].arg);
			matched = 1;
			अवरोध;
		पूर्ण
		++i;
	पूर्ण

	अगर (!matched)
		ख_लिखो(मानक_त्रुटि, "Invalid command\n");
पूर्ण

अटल व्योम usage(व्योम)
अणु
	अगर (is_clx_n_platक्रमm()) अणु
		ख_लिखो(मानक_त्रुटि, "\nThere is limited support of Intel Speed Select features on this platform.\n");
		ख_लिखो(मानक_त्रुटि, "Everything is pre-configured using BIOS options, this tool can't enable any feature in the hardware.\n\n");
	पूर्ण

	म_लिखो("\nUsage:\n");
	म_लिखो("intel-speed-select [OPTIONS] FEATURE COMMAND COMMAND_ARGUMENTS\n");
	म_लिखो("\nUse this tool to enumerate and control the Intel Speed Select Technology features:\n");
	अगर (is_clx_n_platक्रमm())
		म_लिखो("\nFEATURE : [perf-profile|base-freq]\n");
	अन्यथा
		म_लिखो("\nFEATURE : [perf-profile|base-freq|turbo-freq|core-power|turbo-mode]\n");
	म_लिखो("\nFor help on each feature, use -h|--help\n");
	म_लिखो("\tFor example:  intel-speed-select perf-profile -h\n");

	म_लिखो("\nFor additional help on each command for a feature, use --h|--help\n");
	म_लिखो("\tFor example:  intel-speed-select perf-profile get-lock-status -h\n");
	म_लिखो("\t\t This will print help for the command \"get-lock-status\" for the feature \"perf-profile\"\n");

	म_लिखो("\nOPTIONS\n");
	म_लिखो("\t[-c|--cpu] : logical cpu number\n");
	म_लिखो("\t\tDefault: Die scoped for all dies in the system with multiple dies/package\n");
	म_लिखो("\t\t\t Or Package scoped for all Packages when each package contains one die\n");
	म_लिखो("\t[-d|--debug] : Debug mode\n");
	म_लिखो("\t[-f|--format] : output format [json|text]. Default: text\n");
	म_लिखो("\t[-h|--help] : Print help\n");
	म_लिखो("\t[-i|--info] : Print platform information\n");
	म_लिखो("\t[-a|--all-cpus-online] : Force online every CPU in the system\n");
	म_लिखो("\t[-o|--out] : Output file\n");
	म_लिखो("\t\t\tDefault : stderr\n");
	म_लिखो("\t[-p|--pause] : Delay between two mail box commands in milliseconds\n");
	म_लिखो("\t[-r|--retry] : Retry count for mail box commands on failure, default 3\n");
	म_लिखो("\t[-v|--version] : Print version\n");

	म_लिखो("\nResult format\n");
	म_लिखो("\tResult display uses a common format for each command:\n");
	म_लिखो("\tResults are formatted in text/JSON with\n");
	म_लिखो("\t\tPackage, Die, CPU, and command specific results.\n");

	म_लिखो("\nExamples\n");
	म_लिखो("\tTo get platform information:\n");
	म_लिखो("\t\tintel-speed-select --info\n");
	म_लिखो("\tTo get full perf-profile information dump:\n");
	म_लिखो("\t\tintel-speed-select perf-profile info\n");
	म_लिखो("\tTo get full base-freq information dump:\n");
	म_लिखो("\t\tintel-speed-select base-freq info -l 0\n");
	अगर (!is_clx_n_platक्रमm()) अणु
		म_लिखो("\tTo get full turbo-freq information dump:\n");
		म_लिखो("\t\tintel-speed-select turbo-freq info -l 0\n");
	पूर्ण
	निकास(1);
पूर्ण

अटल व्योम prपूर्णांक_version(व्योम)
अणु
	ख_लिखो(outf, "Version %s\n", version_str);
	निकास(0);
पूर्ण

अटल व्योम cmdline(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *pathname = "/dev/isst_interface";
	अक्षर *ptr;
	खाता *fp;
	पूर्णांक opt, क्रमce_cpus_online = 0;
	पूर्णांक option_index = 0;
	पूर्णांक ret;

	अटल काष्ठा option दीर्घ_options[] = अणु
		अणु "all-cpus-online", no_argument, 0, 'a' पूर्ण,
		अणु "cpu", required_argument, 0, 'c' पूर्ण,
		अणु "debug", no_argument, 0, 'd' पूर्ण,
		अणु "format", required_argument, 0, 'f' पूर्ण,
		अणु "help", no_argument, 0, 'h' पूर्ण,
		अणु "info", no_argument, 0, 'i' पूर्ण,
		अणु "pause", required_argument, 0, 'p' पूर्ण,
		अणु "out", required_argument, 0, 'o' पूर्ण,
		अणु "retry", required_argument, 0, 'r' पूर्ण,
		अणु "version", no_argument, 0, 'v' पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;

	अगर (geteuid() != 0) अणु
		ख_लिखो(मानक_त्रुटि, "Must run as root\n");
		निकास(0);
	पूर्ण

	ret = update_cpu_model();
	अगर (ret)
		err(-1, "Invalid CPU model (%d)\n", cpu_model);
	म_लिखो("Intel(R) Speed Select Technology\n");
	म_लिखो("Executing on CPU model:%d[0x%x]\n", cpu_model, cpu_model);

	अगर (!is_clx_n_platक्रमm()) अणु
		fp = ख_खोलो(pathname, "rb");
		अगर (!fp) अणु
			ख_लिखो(मानक_त्रुटि, "Intel speed select drivers are not loaded on this system.\n");
			ख_लिखो(मानक_त्रुटि, "Verify that kernel config includes CONFIG_INTEL_SPEED_SELECT_INTERFACE.\n");
			ख_लिखो(मानक_त्रुटि, "If the config is included then this is not a supported platform.\n");
			निकास(0);
		पूर्ण
		ख_बंद(fp);
	पूर्ण

	progname = argv[0];
	जबतक ((opt = getopt_दीर्घ_only(argc, argv, "+c:df:hio:va", दीर्घ_options,
				       &option_index)) != -1) अणु
		चयन (opt) अणु
		हाल 'a':
			क्रमce_cpus_online = 1;
			अवरोध;
		हाल 'c':
			parse_cpu_command(optarg);
			अवरोध;
		हाल 'd':
			debug_flag = 1;
			म_लिखो("Debug Mode ON\n");
			अवरोध;
		हाल 'f':
			अगर (!म_भेदन(optarg, "json", 4))
				out_क्रमmat_json = 1;
			अवरोध;
		हाल 'h':
			usage();
			अवरोध;
		हाल 'i':
			isst_prपूर्णांक_platक्रमm_inक्रमmation();
			अवरोध;
		हाल 'o':
			अगर (outf)
				ख_बंद(outf);
			outf = ख_खोलो_or_निकास(optarg, "w");
			अवरोध;
		हाल 'p':
			ret = म_से_दीर्घ(optarg, &ptr, 10);
			अगर (!ret)
				ख_लिखो(मानक_त्रुटि, "Invalid pause interval, ignore\n");
			अन्यथा
				mbox_delay = ret;
			अवरोध;
		हाल 'r':
			ret = म_से_दीर्घ(optarg, &ptr, 10);
			अगर (!ret)
				ख_लिखो(मानक_त्रुटि, "Invalid retry count, ignore\n");
			अन्यथा
				mbox_retries = ret;
			अवरोध;
		हाल 'v':
			prपूर्णांक_version();
			अवरोध;
		शेष:
			usage();
		पूर्ण
	पूर्ण

	अगर (optind > (argc - 2)) अणु
		usage();
		निकास(0);
	पूर्ण
	set_max_cpu_num();
	अगर (क्रमce_cpus_online)
		क्रमce_all_cpus_online();
	store_cpu_topology();
	set_cpu_present_cpu_mask();
	set_cpu_target_cpu_mask();

	अगर (!is_clx_n_platक्रमm()) अणु
		ret = isst_fill_platक्रमm_info();
		अगर (ret)
			जाओ out;
		process_command(argc, argv, isst_help_cmds, isst_cmds);
	पूर्ण अन्यथा अणु
		process_command(argc, argv, clx_n_help_cmds, clx_n_cmds);
	पूर्ण
out:
	मुक्त_cpu_set(present_cpumask);
	मुक्त_cpu_set(target_cpumask);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	outf = मानक_त्रुटि;
	cmdline(argc, argv);
	वापस 0;
पूर्ण
