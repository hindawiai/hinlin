<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * coretemp.c - Linux kernel module क्रम hardware monitoring
 *
 * Copyright (C) 2007 Ruकरोlf Marek <r.marek@assembler.cz>
 *
 * Inspired from many hwmon drivers
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpu_device_id.h>

#घोषणा DRVNAME	"coretemp"

/*
 * क्रमce_tjmax only matters when TjMax can't be पढ़ो from the CPU itself.
 * When set, it replaces the driver's suboptimal heuristic.
 */
अटल पूर्णांक क्रमce_tjmax;
module_param_named(tjmax, क्रमce_tjmax, पूर्णांक, 0444);
MODULE_PARM_DESC(tjmax, "TjMax value in degrees Celsius");

#घोषणा PKG_SYSFS_ATTR_NO	1	/* Sysfs attribute क्रम package temp */
#घोषणा BASE_SYSFS_ATTR_NO	2	/* Sysfs Base attr no क्रम coretemp */
#घोषणा NUM_REAL_CORES		128	/* Number of Real cores per cpu */
#घोषणा CORETEMP_NAME_LENGTH	19	/* String Length of attrs */
#घोषणा MAX_CORE_ATTRS		4	/* Maximum no of basic attrs */
#घोषणा TOTAL_ATTRS		(MAX_CORE_ATTRS + 1)
#घोषणा MAX_CORE_DATA		(NUM_REAL_CORES + BASE_SYSFS_ATTR_NO)

#घोषणा TO_CORE_ID(cpu)		(cpu_data(cpu).cpu_core_id)
#घोषणा TO_ATTR_NO(cpu)		(TO_CORE_ID(cpu) + BASE_SYSFS_ATTR_NO)

#अगर_घोषित CONFIG_SMP
#घोषणा क्रम_each_sibling(i, cpu) \
	क्रम_each_cpu(i, topology_sibling_cpumask(cpu))
#अन्यथा
#घोषणा क्रम_each_sibling(i, cpu)	क्रम (i = 0; false; )
#पूर्ण_अगर

/*
 * Per-Core Temperature Data
 * @last_updated: The समय when the current temperature value was updated
 *		earlier (in jअगरfies).
 * @cpu_core_id: The CPU Core from which temperature values should be पढ़ो
 *		This value is passed as "id" field to rdmsr/wrmsr functions.
 * @status_reg: One of IA32_THERM_STATUS or IA32_PACKAGE_THERM_STATUS,
 *		from where the temperature values should be पढ़ो.
 * @attr_size:  Total number of pre-core attrs displayed in the sysfs.
 * @is_pkg_data: If this is 1, the temp_data holds pkgtemp data.
 *		Otherwise, temp_data holds coretemp data.
 * @valid: If this is 1, the current temperature is valid.
 */
काष्ठा temp_data अणु
	पूर्णांक temp;
	पूर्णांक ttarget;
	पूर्णांक tjmax;
	अचिन्हित दीर्घ last_updated;
	अचिन्हित पूर्णांक cpu;
	u32 cpu_core_id;
	u32 status_reg;
	पूर्णांक attr_size;
	bool is_pkg_data;
	bool valid;
	काष्ठा sensor_device_attribute sd_attrs[TOTAL_ATTRS];
	अक्षर attr_name[TOTAL_ATTRS][CORETEMP_NAME_LENGTH];
	काष्ठा attribute *attrs[TOTAL_ATTRS + 1];
	काष्ठा attribute_group attr_group;
	काष्ठा mutex update_lock;
पूर्ण;

/* Platक्रमm Data per Physical CPU */
काष्ठा platक्रमm_data अणु
	काष्ठा device		*hwmon_dev;
	u16			pkg_id;
	काष्ठा cpumask		cpumask;
	काष्ठा temp_data	*core_data[MAX_CORE_DATA];
	काष्ठा device_attribute name_attr;
पूर्ण;

/* Keep track of how many zone poपूर्णांकers we allocated in init() */
अटल पूर्णांक max_zones __पढ़ो_mostly;
/* Array of zone poपूर्णांकers. Serialized by cpu hotplug lock */
अटल काष्ठा platक्रमm_device **zone_devices;

अटल sमाप_प्रकार show_label(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा platक्रमm_data *pdata = dev_get_drvdata(dev);
	काष्ठा temp_data *tdata = pdata->core_data[attr->index];

	अगर (tdata->is_pkg_data)
		वापस प्र_लिखो(buf, "Package id %u\n", pdata->pkg_id);

	वापस प्र_लिखो(buf, "Core %u\n", tdata->cpu_core_id);
पूर्ण

अटल sमाप_प्रकार show_crit_alarm(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	u32 eax, edx;
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा platक्रमm_data *pdata = dev_get_drvdata(dev);
	काष्ठा temp_data *tdata = pdata->core_data[attr->index];

	mutex_lock(&tdata->update_lock);
	rdmsr_on_cpu(tdata->cpu, tdata->status_reg, &eax, &edx);
	mutex_unlock(&tdata->update_lock);

	वापस प्र_लिखो(buf, "%d\n", (eax >> 5) & 1);
पूर्ण

अटल sमाप_प्रकार show_tjmax(काष्ठा device *dev,
			काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा platक्रमm_data *pdata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", pdata->core_data[attr->index]->tjmax);
पूर्ण

अटल sमाप_प्रकार show_ttarget(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा platक्रमm_data *pdata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", pdata->core_data[attr->index]->ttarget);
पूर्ण

अटल sमाप_प्रकार show_temp(काष्ठा device *dev,
			काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	u32 eax, edx;
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा platक्रमm_data *pdata = dev_get_drvdata(dev);
	काष्ठा temp_data *tdata = pdata->core_data[attr->index];

	mutex_lock(&tdata->update_lock);

	/* Check whether the समय पूर्णांकerval has elapsed */
	अगर (!tdata->valid || समय_after(jअगरfies, tdata->last_updated + HZ)) अणु
		rdmsr_on_cpu(tdata->cpu, tdata->status_reg, &eax, &edx);
		/*
		 * Ignore the valid bit. In all observed हालs the रेजिस्टर
		 * value is either low or zero अगर the valid bit is 0.
		 * Return it instead of reporting an error which करोesn't
		 * really help at all.
		 */
		tdata->temp = tdata->tjmax - ((eax >> 16) & 0x7f) * 1000;
		tdata->valid = 1;
		tdata->last_updated = jअगरfies;
	पूर्ण

	mutex_unlock(&tdata->update_lock);
	वापस प्र_लिखो(buf, "%d\n", tdata->temp);
पूर्ण

काष्ठा tjmax_pci अणु
	अचिन्हित पूर्णांक device;
	पूर्णांक tjmax;
पूर्ण;

अटल स्थिर काष्ठा tjmax_pci tjmax_pci_table[] = अणु
	अणु 0x0708, 110000 पूर्ण,	/* CE41x0 (Sodaville ) */
	अणु 0x0c72, 102000 पूर्ण,	/* Atom S1240 (Centerton) */
	अणु 0x0c73, 95000 पूर्ण,	/* Atom S1220 (Centerton) */
	अणु 0x0c75, 95000 पूर्ण,	/* Atom S1260 (Centerton) */
पूर्ण;

काष्ठा tjmax अणु
	अक्षर स्थिर *id;
	पूर्णांक tjmax;
पूर्ण;

अटल स्थिर काष्ठा tjmax tjmax_table[] = अणु
	अणु "CPU  230", 100000 पूर्ण,		/* Model 0x1c, stepping 2	*/
	अणु "CPU  330", 125000 पूर्ण,		/* Model 0x1c, stepping 2	*/
पूर्ण;

काष्ठा tjmax_model अणु
	u8 model;
	u8 mask;
	पूर्णांक tjmax;
पूर्ण;

#घोषणा ANY 0xff

अटल स्थिर काष्ठा tjmax_model tjmax_model_table[] = अणु
	अणु 0x1c, 10, 100000 पूर्ण,	/* D4xx, K4xx, N4xx, D5xx, K5xx, N5xx */
	अणु 0x1c, ANY, 90000 पूर्ण,	/* Z5xx, N2xx, possibly others
				 * Note: Also matches 230 and 330,
				 * which are covered by tjmax_table
				 */
	अणु 0x26, ANY, 90000 पूर्ण,	/* Atom Tunnel Creek (Exx), Lincroft (Z6xx)
				 * Note: TjMax क्रम E6xxT is 110C, but CPU type
				 * is undetectable by software
				 */
	अणु 0x27, ANY, 90000 पूर्ण,	/* Atom Medfield (Z2460) */
	अणु 0x35, ANY, 90000 पूर्ण,	/* Atom Clover Trail/Cloverview (Z27x0) */
	अणु 0x36, ANY, 100000 पूर्ण,	/* Atom Cedar Trail/Cedarview (N2xxx, D2xxx)
				 * Also matches S12x0 (stepping 9), covered by
				 * PCI table
				 */
पूर्ण;

अटल पूर्णांक adjust_tjmax(काष्ठा cpuinfo_x86 *c, u32 id, काष्ठा device *dev)
अणु
	/* The 100C is शेष क्रम both mobile and non mobile CPUs */

	पूर्णांक tjmax = 100000;
	पूर्णांक tjmax_ee = 85000;
	पूर्णांक usemsr_ee = 1;
	पूर्णांक err;
	u32 eax, edx;
	पूर्णांक i;
	u16 devfn = PCI_DEVFN(0, 0);
	काष्ठा pci_dev *host_bridge = pci_get_करोमुख्य_bus_and_slot(0, 0, devfn);

	/*
	 * Explicit tjmax table entries override heuristics.
	 * First try PCI host bridge IDs, followed by model ID strings
	 * and model/stepping inक्रमmation.
	 */
	अगर (host_bridge && host_bridge->venकरोr == PCI_VENDOR_ID_INTEL) अणु
		क्रम (i = 0; i < ARRAY_SIZE(tjmax_pci_table); i++) अणु
			अगर (host_bridge->device == tjmax_pci_table[i].device)
				वापस tjmax_pci_table[i].tjmax;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tjmax_table); i++) अणु
		अगर (म_माला(c->x86_model_id, tjmax_table[i].id))
			वापस tjmax_table[i].tjmax;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tjmax_model_table); i++) अणु
		स्थिर काष्ठा tjmax_model *पंचांग = &tjmax_model_table[i];
		अगर (c->x86_model == पंचांग->model &&
		    (पंचांग->mask == ANY || c->x86_stepping == पंचांग->mask))
			वापस पंचांग->tjmax;
	पूर्ण

	/* Early chips have no MSR क्रम TjMax */

	अगर (c->x86_model == 0xf && c->x86_stepping < 4)
		usemsr_ee = 0;

	अगर (c->x86_model > 0xe && usemsr_ee) अणु
		u8 platक्रमm_id;

		/*
		 * Now we can detect the mobile CPU using Intel provided table
		 * http://softwarecommunity.पूर्णांकel.com/Wiki/Mobility/720.hपंचांग
		 * For Core2 cores, check MSR 0x17, bit 28 1 = Mobile CPU
		 */
		err = rdmsr_safe_on_cpu(id, 0x17, &eax, &edx);
		अगर (err) अणु
			dev_warn(dev,
				 "Unable to access MSR 0x17, assuming desktop"
				 " CPU\n");
			usemsr_ee = 0;
		पूर्ण अन्यथा अगर (c->x86_model < 0x17 && !(eax & 0x10000000)) अणु
			/*
			 * Trust bit 28 up to Penryn, I could not find any
			 * करोcumentation on that; अगर you happen to know
			 * someone at Intel please ask
			 */
			usemsr_ee = 0;
		पूर्ण अन्यथा अणु
			/* Platक्रमm ID bits 52:50 (EDX starts at bit 32) */
			platक्रमm_id = (edx >> 18) & 0x7;

			/*
			 * Mobile Penryn CPU seems to be platक्रमm ID 7 or 5
			 * (guesswork)
			 */
			अगर (c->x86_model == 0x17 &&
			    (platक्रमm_id == 5 || platक्रमm_id == 7)) अणु
				/*
				 * If MSR EE bit is set, set it to 90 degrees C,
				 * otherwise 105 degrees C
				 */
				tjmax_ee = 90000;
				tjmax = 105000;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (usemsr_ee) अणु
		err = rdmsr_safe_on_cpu(id, 0xee, &eax, &edx);
		अगर (err) अणु
			dev_warn(dev,
				 "Unable to access MSR 0xEE, for Tjmax, left"
				 " at default\n");
		पूर्ण अन्यथा अगर (eax & 0x40000000) अणु
			tjmax = tjmax_ee;
		पूर्ण
	पूर्ण अन्यथा अगर (tjmax == 100000) अणु
		/*
		 * If we करोn't use msr EE it means we are desktop CPU
		 * (with exeception of Atom)
		 */
		dev_warn(dev, "Using relative temperature scale!\n");
	पूर्ण

	वापस tjmax;
पूर्ण

अटल bool cpu_has_tjmax(काष्ठा cpuinfo_x86 *c)
अणु
	u8 model = c->x86_model;

	वापस model > 0xe &&
	       model != 0x1c &&
	       model != 0x26 &&
	       model != 0x27 &&
	       model != 0x35 &&
	       model != 0x36;
पूर्ण

अटल पूर्णांक get_tjmax(काष्ठा cpuinfo_x86 *c, u32 id, काष्ठा device *dev)
अणु
	पूर्णांक err;
	u32 eax, edx;
	u32 val;

	/*
	 * A new feature of current Intel(R) processors, the
	 * IA32_TEMPERATURE_TARGET contains the TjMax value
	 */
	err = rdmsr_safe_on_cpu(id, MSR_IA32_TEMPERATURE_TARGET, &eax, &edx);
	अगर (err) अणु
		अगर (cpu_has_tjmax(c))
			dev_warn(dev, "Unable to read TjMax from CPU %u\n", id);
	पूर्ण अन्यथा अणु
		val = (eax >> 16) & 0xff;
		/*
		 * If the TjMax is not plausible, an assumption
		 * will be used
		 */
		अगर (val) अणु
			dev_dbg(dev, "TjMax is %d degrees C\n", val);
			वापस val * 1000;
		पूर्ण
	पूर्ण

	अगर (क्रमce_tjmax) अणु
		dev_notice(dev, "TjMax forced to %d degrees C by user\n",
			   क्रमce_tjmax);
		वापस क्रमce_tjmax * 1000;
	पूर्ण

	/*
	 * An assumption is made क्रम early CPUs and unपढ़ोable MSR.
	 * NOTE: the calculated value may not be correct.
	 */
	वापस adjust_tjmax(c, id, dev);
पूर्ण

अटल पूर्णांक create_core_attrs(काष्ठा temp_data *tdata, काष्ठा device *dev,
			     पूर्णांक attr_no)
अणु
	पूर्णांक i;
	अटल sमाप_प्रकार (*स्थिर rd_ptr[TOTAL_ATTRS]) (काष्ठा device *dev,
			काष्ठा device_attribute *devattr, अक्षर *buf) = अणु
			show_label, show_crit_alarm, show_temp, show_tjmax,
			show_ttarget पूर्ण;
	अटल स्थिर अक्षर *स्थिर suffixes[TOTAL_ATTRS] = अणु
		"label", "crit_alarm", "input", "crit", "max"
	पूर्ण;

	क्रम (i = 0; i < tdata->attr_size; i++) अणु
		snम_लिखो(tdata->attr_name[i], CORETEMP_NAME_LENGTH,
			 "temp%d_%s", attr_no, suffixes[i]);
		sysfs_attr_init(&tdata->sd_attrs[i].dev_attr.attr);
		tdata->sd_attrs[i].dev_attr.attr.name = tdata->attr_name[i];
		tdata->sd_attrs[i].dev_attr.attr.mode = 0444;
		tdata->sd_attrs[i].dev_attr.show = rd_ptr[i];
		tdata->sd_attrs[i].index = attr_no;
		tdata->attrs[i] = &tdata->sd_attrs[i].dev_attr.attr;
	पूर्ण
	tdata->attr_group.attrs = tdata->attrs;
	वापस sysfs_create_group(&dev->kobj, &tdata->attr_group);
पूर्ण


अटल पूर्णांक chk_ucode_version(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

	/*
	 * Check अगर we have problem with errata AE18 of Core processors:
	 * Readings might stop update when processor visited too deep sleep,
	 * fixed क्रम stepping D0 (6EC).
	 */
	अगर (c->x86_model == 0xe && c->x86_stepping < 0xc && c->microcode < 0x39) अणु
		pr_err("Errata AE18 not fixed, update BIOS or microcode of the CPU!\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device *coretemp_get_pdev(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक id = topology_logical_die_id(cpu);

	अगर (id >= 0 && id < max_zones)
		वापस zone_devices[id];
	वापस शून्य;
पूर्ण

अटल काष्ठा temp_data *init_temp_data(अचिन्हित पूर्णांक cpu, पूर्णांक pkg_flag)
अणु
	काष्ठा temp_data *tdata;

	tdata = kzalloc(माप(काष्ठा temp_data), GFP_KERNEL);
	अगर (!tdata)
		वापस शून्य;

	tdata->status_reg = pkg_flag ? MSR_IA32_PACKAGE_THERM_STATUS :
							MSR_IA32_THERM_STATUS;
	tdata->is_pkg_data = pkg_flag;
	tdata->cpu = cpu;
	tdata->cpu_core_id = TO_CORE_ID(cpu);
	tdata->attr_size = MAX_CORE_ATTRS;
	mutex_init(&tdata->update_lock);
	वापस tdata;
पूर्ण

अटल पूर्णांक create_core_data(काष्ठा platक्रमm_device *pdev, अचिन्हित पूर्णांक cpu,
			    पूर्णांक pkg_flag)
अणु
	काष्ठा temp_data *tdata;
	काष्ठा platक्रमm_data *pdata = platक्रमm_get_drvdata(pdev);
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	u32 eax, edx;
	पूर्णांक err, attr_no;

	/*
	 * Find attr number क्रम sysfs:
	 * We map the attr number to core id of the CPU
	 * The attr number is always core id + 2
	 * The Pkgtemp will always show up as temp1_*, अगर available
	 */
	attr_no = pkg_flag ? PKG_SYSFS_ATTR_NO : TO_ATTR_NO(cpu);

	अगर (attr_no > MAX_CORE_DATA - 1)
		वापस -दुस्फल;

	tdata = init_temp_data(cpu, pkg_flag);
	अगर (!tdata)
		वापस -ENOMEM;

	/* Test अगर we can access the status रेजिस्टर */
	err = rdmsr_safe_on_cpu(cpu, tdata->status_reg, &eax, &edx);
	अगर (err)
		जाओ निकास_मुक्त;

	/* We can access status रेजिस्टर. Get Critical Temperature */
	tdata->tjmax = get_tjmax(c, cpu, &pdev->dev);

	/*
	 * Read the still unकरोcumented bits 8:15 of IA32_TEMPERATURE_TARGET.
	 * The target temperature is available on older CPUs but not in this
	 * रेजिस्टर. Atoms करोn't have the रेजिस्टर at all.
	 */
	अगर (c->x86_model > 0xe && c->x86_model != 0x1c) अणु
		err = rdmsr_safe_on_cpu(cpu, MSR_IA32_TEMPERATURE_TARGET,
					&eax, &edx);
		अगर (!err) अणु
			tdata->ttarget
			  = tdata->tjmax - ((eax >> 8) & 0xff) * 1000;
			tdata->attr_size++;
		पूर्ण
	पूर्ण

	pdata->core_data[attr_no] = tdata;

	/* Create sysfs पूर्णांकerfaces */
	err = create_core_attrs(tdata, pdata->hwmon_dev, attr_no);
	अगर (err)
		जाओ निकास_मुक्त;

	वापस 0;
निकास_मुक्त:
	pdata->core_data[attr_no] = शून्य;
	kमुक्त(tdata);
	वापस err;
पूर्ण

अटल व्योम
coretemp_add_core(काष्ठा platक्रमm_device *pdev, अचिन्हित पूर्णांक cpu, पूर्णांक pkg_flag)
अणु
	अगर (create_core_data(pdev, cpu, pkg_flag))
		dev_err(&pdev->dev, "Adding Core %u failed\n", cpu);
पूर्ण

अटल व्योम coretemp_हटाओ_core(काष्ठा platक्रमm_data *pdata, पूर्णांक indx)
अणु
	काष्ठा temp_data *tdata = pdata->core_data[indx];

	/* Remove the sysfs attributes */
	sysfs_हटाओ_group(&pdata->hwmon_dev->kobj, &tdata->attr_group);

	kमुक्त(pdata->core_data[indx]);
	pdata->core_data[indx] = शून्य;
पूर्ण

अटल पूर्णांक coretemp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा platक्रमm_data *pdata;

	/* Initialize the per-zone data काष्ठाures */
	pdata = devm_kzalloc(dev, माप(काष्ठा platक्रमm_data), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->pkg_id = pdev->id;
	platक्रमm_set_drvdata(pdev, pdata);

	pdata->hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, DRVNAME,
								  pdata, शून्य);
	वापस PTR_ERR_OR_ZERO(pdata->hwmon_dev);
पूर्ण

अटल पूर्णांक coretemp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_data *pdata = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = MAX_CORE_DATA - 1; i >= 0; --i)
		अगर (pdata->core_data[i])
			coretemp_हटाओ_core(pdata, i);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver coretemp_driver = अणु
	.driver = अणु
		.name = DRVNAME,
	पूर्ण,
	.probe = coretemp_probe,
	.हटाओ = coretemp_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_device *coretemp_device_add(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक err, zoneid = topology_logical_die_id(cpu);
	काष्ठा platक्रमm_device *pdev;

	अगर (zoneid < 0)
		वापस ERR_PTR(-ENOMEM);

	pdev = platक्रमm_device_alloc(DRVNAME, zoneid);
	अगर (!pdev)
		वापस ERR_PTR(-ENOMEM);

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		platक्रमm_device_put(pdev);
		वापस ERR_PTR(err);
	पूर्ण

	zone_devices[zoneid] = pdev;
	वापस pdev;
पूर्ण

अटल पूर्णांक coretemp_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा platक्रमm_device *pdev = coretemp_get_pdev(cpu);
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	काष्ठा platक्रमm_data *pdata;

	/*
	 * Don't execute this on resume as the offline callback did
	 * not get executed on suspend.
	 */
	अगर (cpuhp_tasks_frozen)
		वापस 0;

	/*
	 * CPUID.06H.EAX[0] indicates whether the CPU has thermal
	 * sensors. We check this bit only, all the early CPUs
	 * without thermal sensors will be filtered out.
	 */
	अगर (!cpu_has(c, X86_FEATURE_DTHERM))
		वापस -ENODEV;

	अगर (!pdev) अणु
		/* Check the microcode version of the CPU */
		अगर (chk_ucode_version(cpu))
			वापस -EINVAL;

		/*
		 * Alright, we have DTS support.
		 * We are bringing the _first_ core in this pkg
		 * online. So, initialize per-pkg data काष्ठाures and
		 * then bring this core online.
		 */
		pdev = coretemp_device_add(cpu);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);

		/*
		 * Check whether pkgtemp support is available.
		 * If so, add पूर्णांकerfaces क्रम pkgtemp.
		 */
		अगर (cpu_has(c, X86_FEATURE_PTS))
			coretemp_add_core(pdev, cpu, 1);
	पूर्ण

	pdata = platक्रमm_get_drvdata(pdev);
	/*
	 * Check whether a thपढ़ो sibling is alपढ़ोy online. If not add the
	 * पूर्णांकerface क्रम this CPU core.
	 */
	अगर (!cpumask_पूर्णांकersects(&pdata->cpumask, topology_sibling_cpumask(cpu)))
		coretemp_add_core(pdev, cpu, 0);

	cpumask_set_cpu(cpu, &pdata->cpumask);
	वापस 0;
पूर्ण

अटल पूर्णांक coretemp_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा platक्रमm_device *pdev = coretemp_get_pdev(cpu);
	काष्ठा platक्रमm_data *pd;
	काष्ठा temp_data *tdata;
	पूर्णांक indx, target;

	/*
	 * Don't execute this on suspend as the device हटाओ locks
	 * up the machine.
	 */
	अगर (cpuhp_tasks_frozen)
		वापस 0;

	/* If the physical CPU device करोes not exist, just वापस */
	अगर (!pdev)
		वापस 0;

	/* The core id is too big, just वापस */
	indx = TO_ATTR_NO(cpu);
	अगर (indx > MAX_CORE_DATA - 1)
		वापस 0;

	pd = platक्रमm_get_drvdata(pdev);
	tdata = pd->core_data[indx];

	cpumask_clear_cpu(cpu, &pd->cpumask);

	/*
	 * If this is the last thपढ़ो sibling, हटाओ the CPU core
	 * पूर्णांकerface, If there is still a sibling online, transfer the
	 * target cpu of that core पूर्णांकerface to it.
	 */
	target = cpumask_any_and(&pd->cpumask, topology_sibling_cpumask(cpu));
	अगर (target >= nr_cpu_ids) अणु
		coretemp_हटाओ_core(pd, indx);
	पूर्ण अन्यथा अगर (tdata && tdata->cpu == cpu) अणु
		mutex_lock(&tdata->update_lock);
		tdata->cpu = target;
		mutex_unlock(&tdata->update_lock);
	पूर्ण

	/*
	 * If all cores in this pkg are offline, हटाओ the device. This
	 * will invoke the platक्रमm driver हटाओ function, which cleans up
	 * the rest.
	 */
	अगर (cpumask_empty(&pd->cpumask)) अणु
		zone_devices[topology_logical_die_id(cpu)] = शून्य;
		platक्रमm_device_unरेजिस्टर(pdev);
		वापस 0;
	पूर्ण

	/*
	 * Check whether this core is the target क्रम the package
	 * पूर्णांकerface. We need to assign it to some other cpu.
	 */
	tdata = pd->core_data[PKG_SYSFS_ATTR_NO];
	अगर (tdata && tdata->cpu == cpu) अणु
		target = cpumask_first(&pd->cpumask);
		mutex_lock(&tdata->update_lock);
		tdata->cpu = target;
		mutex_unlock(&tdata->update_lock);
	पूर्ण
	वापस 0;
पूर्ण
अटल स्थिर काष्ठा x86_cpu_id __initस्थिर coretemp_ids[] = अणु
	X86_MATCH_VENDOR_FEATURE(INTEL, X86_FEATURE_DTHERM, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, coretemp_ids);

अटल क्रमागत cpuhp_state coretemp_hp_online;

अटल पूर्णांक __init coretemp_init(व्योम)
अणु
	पूर्णांक err;

	/*
	 * CPUID.06H.EAX[0] indicates whether the CPU has thermal
	 * sensors. We check this bit only, all the early CPUs
	 * without thermal sensors will be filtered out.
	 */
	अगर (!x86_match_cpu(coretemp_ids))
		वापस -ENODEV;

	max_zones = topology_max_packages() * topology_max_die_per_package();
	zone_devices = kसुस्मृति(max_zones, माप(काष्ठा platक्रमm_device *),
			      GFP_KERNEL);
	अगर (!zone_devices)
		वापस -ENOMEM;

	err = platक्रमm_driver_रेजिस्टर(&coretemp_driver);
	अगर (err)
		जाओ outzone;

	err = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "hwmon/coretemp:online",
				coretemp_cpu_online, coretemp_cpu_offline);
	अगर (err < 0)
		जाओ outdrv;
	coretemp_hp_online = err;
	वापस 0;

outdrv:
	platक्रमm_driver_unरेजिस्टर(&coretemp_driver);
outzone:
	kमुक्त(zone_devices);
	वापस err;
पूर्ण
module_init(coretemp_init)

अटल व्योम __निकास coretemp_निकास(व्योम)
अणु
	cpuhp_हटाओ_state(coretemp_hp_online);
	platक्रमm_driver_unरेजिस्टर(&coretemp_driver);
	kमुक्त(zone_devices);
पूर्ण
module_निकास(coretemp_निकास)

MODULE_AUTHOR("Rudolf Marek <r.marek@assembler.cz>");
MODULE_DESCRIPTION("Intel Core temperature monitor");
MODULE_LICENSE("GPL");
