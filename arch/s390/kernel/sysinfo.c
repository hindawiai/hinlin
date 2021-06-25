<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright IBM Corp. 2001, 2009
 *  Author(s): Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
 *	       Martin Schwidefsky <schwidefsky@de.ibm.com>,
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/topology.h>
#समावेश <यंत्र/fpu/api.h>

पूर्णांक topology_max_mnest;

अटल अंतरभूत पूर्णांक __stsi(व्योम *sysinfo, पूर्णांक fc, पूर्णांक sel1, पूर्णांक sel2, पूर्णांक *lvl)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = (fc << 28) | sel1;
	रेजिस्टर पूर्णांक r1 यंत्र("1") = sel2;
	पूर्णांक rc = 0;

	यंत्र अस्थिर(
		"	stsi	0(%3)\n"
		"0:	jz	2f\n"
		"1:	lhi	%1,%4\n"
		"2:\n"
		EX_TABLE(0b, 1b)
		: "+d" (r0), "+d" (rc)
		: "d" (r1), "a" (sysinfo), "K" (-EOPNOTSUPP)
		: "cc", "memory");
	*lvl = ((अचिन्हित पूर्णांक) r0) >> 28;
	वापस rc;
पूर्ण

/*
 * stsi - store प्रणाली inक्रमmation
 *
 * Returns the current configuration level अगर function code 0 was specअगरied.
 * Otherwise वापसs 0 on success or a negative value on error.
 */
पूर्णांक stsi(व्योम *sysinfo, पूर्णांक fc, पूर्णांक sel1, पूर्णांक sel2)
अणु
	पूर्णांक lvl, rc;

	rc = __stsi(sysinfo, fc, sel1, sel2, &lvl);
	अगर (rc)
		वापस rc;
	वापस fc ? 0 : lvl;
पूर्ण
EXPORT_SYMBOL(stsi);

#अगर_घोषित CONFIG_PROC_FS

अटल bool convert_ext_name(अचिन्हित अक्षर encoding, अक्षर *name, माप_प्रकार len)
अणु
	चयन (encoding) अणु
	हाल 1: /* EBCDIC */
		EBCASC(name, len);
		अवरोध;
	हाल 2:	/* UTF-8 */
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम stsi_1_1_1(काष्ठा seq_file *m, काष्ठा sysinfo_1_1_1 *info)
अणु
	पूर्णांक i;

	अगर (stsi(info, 1, 1, 1))
		वापस;
	EBCASC(info->manufacturer, माप(info->manufacturer));
	EBCASC(info->type, माप(info->type));
	EBCASC(info->model, माप(info->model));
	EBCASC(info->sequence, माप(info->sequence));
	EBCASC(info->plant, माप(info->plant));
	EBCASC(info->model_capacity, माप(info->model_capacity));
	EBCASC(info->model_perm_cap, माप(info->model_perm_cap));
	EBCASC(info->model_temp_cap, माप(info->model_temp_cap));
	seq_म_लिखो(m, "Manufacturer:         %-16.16s\n", info->manufacturer);
	seq_म_लिखो(m, "Type:                 %-4.4s\n", info->type);
	अगर (info->lic)
		seq_म_लिखो(m, "LIC Identifier:       %016lx\n", info->lic);
	/*
	 * Sigh: the model field has been नामd with System z9
	 * to model_capacity and a new model field has been added
	 * after the plant field. To aव्योम confusing older programs
	 * the "Model:" prपूर्णांकs "model_capacity model" or just
	 * "model_capacity" अगर the model string is empty .
	 */
	seq_म_लिखो(m, "Model:                %-16.16s", info->model_capacity);
	अगर (info->model[0] != '\0')
		seq_म_लिखो(m, " %-16.16s", info->model);
	seq_अ_दो(m, '\n');
	seq_म_लिखो(m, "Sequence Code:        %-16.16s\n", info->sequence);
	seq_म_लिखो(m, "Plant:                %-4.4s\n", info->plant);
	seq_म_लिखो(m, "Model Capacity:       %-16.16s %08u\n",
		   info->model_capacity, info->model_cap_rating);
	अगर (info->model_perm_cap_rating)
		seq_म_लिखो(m, "Model Perm. Capacity: %-16.16s %08u\n",
			   info->model_perm_cap,
			   info->model_perm_cap_rating);
	अगर (info->model_temp_cap_rating)
		seq_म_लिखो(m, "Model Temp. Capacity: %-16.16s %08u\n",
			   info->model_temp_cap,
			   info->model_temp_cap_rating);
	अगर (info->ncr)
		seq_म_लिखो(m, "Nominal Cap. Rating:  %08u\n", info->ncr);
	अगर (info->npr)
		seq_म_लिखो(m, "Nominal Perm. Rating: %08u\n", info->npr);
	अगर (info->ntr)
		seq_म_लिखो(m, "Nominal Temp. Rating: %08u\n", info->ntr);
	अगर (info->cai) अणु
		seq_म_लिखो(m, "Capacity Adj. Ind.:   %d\n", info->cai);
		seq_म_लिखो(m, "Capacity Ch. Reason:  %d\n", info->ccr);
		seq_म_लिखो(m, "Capacity Transient:   %d\n", info->t);
	पूर्ण
	अगर (info->p) अणु
		क्रम (i = 1; i <= ARRAY_SIZE(info->typepct); i++) अणु
			seq_म_लिखो(m, "Type %d Percentage:    %d\n",
				   i, info->typepct[i - 1]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम stsi_15_1_x(काष्ठा seq_file *m, काष्ठा sysinfo_15_1_x *info)
अणु
	पूर्णांक i;

	seq_अ_दो(m, '\n');
	अगर (!MACHINE_HAS_TOPOLOGY)
		वापस;
	अगर (stsi(info, 15, 1, topology_max_mnest))
		वापस;
	seq_म_लिखो(m, "CPU Topology HW:     ");
	क्रम (i = 0; i < TOPOLOGY_NR_MAG; i++)
		seq_म_लिखो(m, " %d", info->mag[i]);
	seq_अ_दो(m, '\n');
#अगर_घोषित CONFIG_SCHED_TOPOLOGY
	store_topology(info);
	seq_म_लिखो(m, "CPU Topology SW:     ");
	क्रम (i = 0; i < TOPOLOGY_NR_MAG; i++)
		seq_म_लिखो(m, " %d", info->mag[i]);
	seq_अ_दो(m, '\n');
#पूर्ण_अगर
पूर्ण

अटल व्योम stsi_1_2_2(काष्ठा seq_file *m, काष्ठा sysinfo_1_2_2 *info)
अणु
	काष्ठा sysinfo_1_2_2_extension *ext;
	पूर्णांक i;

	अगर (stsi(info, 1, 2, 2))
		वापस;
	ext = (काष्ठा sysinfo_1_2_2_extension *)
		((अचिन्हित दीर्घ) info + info->acc_offset);
	seq_म_लिखो(m, "CPUs Total:           %d\n", info->cpus_total);
	seq_म_लिखो(m, "CPUs Configured:      %d\n", info->cpus_configured);
	seq_म_लिखो(m, "CPUs Standby:         %d\n", info->cpus_standby);
	seq_म_लिखो(m, "CPUs Reserved:        %d\n", info->cpus_reserved);
	अगर (info->mt_installed) अणु
		seq_म_लिखो(m, "CPUs G-MTID:          %d\n", info->mt_gtid);
		seq_म_लिखो(m, "CPUs S-MTID:          %d\n", info->mt_stid);
	पूर्ण
	/*
	 * Sigh 2. According to the specअगरication the alternate
	 * capability field is a 32 bit भग्नing poपूर्णांक number
	 * अगर the higher order 8 bits are not zero. Prपूर्णांकing
	 * a भग्नing poपूर्णांक number in the kernel is a no-no,
	 * always prपूर्णांक the number as 32 bit अचिन्हित पूर्णांकeger.
	 * The user-space needs to know about the strange
	 * encoding of the alternate cpu capability.
	 */
	seq_म_लिखो(m, "Capability:           %u", info->capability);
	अगर (info->क्रमmat == 1)
		seq_म_लिखो(m, " %u", ext->alt_capability);
	seq_अ_दो(m, '\n');
	अगर (info->nominal_cap)
		seq_म_लिखो(m, "Nominal Capability:   %d\n", info->nominal_cap);
	अगर (info->secondary_cap)
		seq_म_लिखो(m, "Secondary Capability: %d\n", info->secondary_cap);
	क्रम (i = 2; i <= info->cpus_total; i++) अणु
		seq_म_लिखो(m, "Adjustment %02d-way:    %u",
			   i, info->adjusपंचांगent[i-2]);
		अगर (info->क्रमmat == 1)
			seq_म_लिखो(m, " %u", ext->alt_adjusपंचांगent[i-2]);
		seq_अ_दो(m, '\n');
	पूर्ण
पूर्ण

अटल व्योम stsi_2_2_2(काष्ठा seq_file *m, काष्ठा sysinfo_2_2_2 *info)
अणु
	अगर (stsi(info, 2, 2, 2))
		वापस;
	EBCASC(info->name, माप(info->name));
	seq_अ_दो(m, '\n');
	seq_म_लिखो(m, "LPAR Number:          %d\n", info->lpar_number);
	seq_म_लिखो(m, "LPAR Characteristics: ");
	अगर (info->अक्षरacteristics & LPAR_CHAR_DEDICATED)
		seq_म_लिखो(m, "Dedicated ");
	अगर (info->अक्षरacteristics & LPAR_CHAR_SHARED)
		seq_म_लिखो(m, "Shared ");
	अगर (info->अक्षरacteristics & LPAR_CHAR_LIMITED)
		seq_म_लिखो(m, "Limited ");
	seq_अ_दो(m, '\n');
	seq_म_लिखो(m, "LPAR Name:            %-8.8s\n", info->name);
	seq_म_लिखो(m, "LPAR Adjustment:      %d\n", info->caf);
	seq_म_लिखो(m, "LPAR CPUs Total:      %d\n", info->cpus_total);
	seq_म_लिखो(m, "LPAR CPUs Configured: %d\n", info->cpus_configured);
	seq_म_लिखो(m, "LPAR CPUs Standby:    %d\n", info->cpus_standby);
	seq_म_लिखो(m, "LPAR CPUs Reserved:   %d\n", info->cpus_reserved);
	seq_म_लिखो(m, "LPAR CPUs Dedicated:  %d\n", info->cpus_dedicated);
	seq_म_लिखो(m, "LPAR CPUs Shared:     %d\n", info->cpus_shared);
	अगर (info->mt_installed) अणु
		seq_म_लिखो(m, "LPAR CPUs G-MTID:     %d\n", info->mt_gtid);
		seq_म_लिखो(m, "LPAR CPUs S-MTID:     %d\n", info->mt_stid);
		seq_म_लिखो(m, "LPAR CPUs PS-MTID:    %d\n", info->mt_psmtid);
	पूर्ण
	अगर (convert_ext_name(info->vsne, info->ext_name, माप(info->ext_name))) अणु
		seq_म_लिखो(m, "LPAR Extended Name:   %-.256s\n", info->ext_name);
		seq_म_लिखो(m, "LPAR UUID:            %pUb\n", &info->uuid);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_ext_name(काष्ठा seq_file *m, पूर्णांक lvl,
			   काष्ठा sysinfo_3_2_2 *info)
अणु
	माप_प्रकार len = माप(info->ext_names[lvl]);

	अगर (!convert_ext_name(info->vm[lvl].evmne, info->ext_names[lvl], len))
		वापस;
	seq_म_लिखो(m, "VM%02d Extended Name:   %-.256s\n", lvl,
		   info->ext_names[lvl]);
पूर्ण

अटल व्योम prपूर्णांक_uuid(काष्ठा seq_file *m, पूर्णांक i, काष्ठा sysinfo_3_2_2 *info)
अणु
	अगर (uuid_is_null(&info->vm[i].uuid))
		वापस;
	seq_म_लिखो(m, "VM%02d UUID:            %pUb\n", i, &info->vm[i].uuid);
पूर्ण

अटल व्योम stsi_3_2_2(काष्ठा seq_file *m, काष्ठा sysinfo_3_2_2 *info)
अणु
	पूर्णांक i;

	अगर (stsi(info, 3, 2, 2))
		वापस;
	क्रम (i = 0; i < info->count; i++) अणु
		EBCASC(info->vm[i].name, माप(info->vm[i].name));
		EBCASC(info->vm[i].cpi, माप(info->vm[i].cpi));
		seq_अ_दो(m, '\n');
		seq_म_लिखो(m, "VM%02d Name:            %-8.8s\n", i, info->vm[i].name);
		seq_म_लिखो(m, "VM%02d Control Program: %-16.16s\n", i, info->vm[i].cpi);
		seq_म_लिखो(m, "VM%02d Adjustment:      %d\n", i, info->vm[i].caf);
		seq_म_लिखो(m, "VM%02d CPUs Total:      %d\n", i, info->vm[i].cpus_total);
		seq_म_लिखो(m, "VM%02d CPUs Configured: %d\n", i, info->vm[i].cpus_configured);
		seq_म_लिखो(m, "VM%02d CPUs Standby:    %d\n", i, info->vm[i].cpus_standby);
		seq_म_लिखो(m, "VM%02d CPUs Reserved:   %d\n", i, info->vm[i].cpus_reserved);
		prपूर्णांक_ext_name(m, i, info);
		prपूर्णांक_uuid(m, i, info);
	पूर्ण
पूर्ण

अटल पूर्णांक sysinfo_show(काष्ठा seq_file *m, व्योम *v)
अणु
	व्योम *info = (व्योम *)get_zeroed_page(GFP_KERNEL);
	पूर्णांक level;

	अगर (!info)
		वापस 0;
	level = stsi(शून्य, 0, 0, 0);
	अगर (level >= 1)
		stsi_1_1_1(m, info);
	अगर (level >= 1)
		stsi_15_1_x(m, info);
	अगर (level >= 1)
		stsi_1_2_2(m, info);
	अगर (level >= 2)
		stsi_2_2_2(m, info);
	अगर (level >= 3)
		stsi_3_2_2(m, info);
	मुक्त_page((अचिन्हित दीर्घ)info);
	वापस 0;
पूर्ण

अटल पूर्णांक __init sysinfo_create_proc(व्योम)
अणु
	proc_create_single("sysinfo", 0444, शून्य, sysinfo_show);
	वापस 0;
पूर्ण
device_initcall(sysinfo_create_proc);

#पूर्ण_अगर /* CONFIG_PROC_FS */

/*
 * Service levels पूर्णांकerface.
 */

अटल DECLARE_RWSEM(service_level_sem);
अटल LIST_HEAD(service_level_list);

पूर्णांक रेजिस्टर_service_level(काष्ठा service_level *slr)
अणु
	काष्ठा service_level *ptr;

	करोwn_ग_लिखो(&service_level_sem);
	list_क्रम_each_entry(ptr, &service_level_list, list)
		अगर (ptr == slr) अणु
			up_ग_लिखो(&service_level_sem);
			वापस -EEXIST;
		पूर्ण
	list_add_tail(&slr->list, &service_level_list);
	up_ग_लिखो(&service_level_sem);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_service_level);

पूर्णांक unरेजिस्टर_service_level(काष्ठा service_level *slr)
अणु
	काष्ठा service_level *ptr, *next;
	पूर्णांक rc = -ENOENT;

	करोwn_ग_लिखो(&service_level_sem);
	list_क्रम_each_entry_safe(ptr, next, &service_level_list, list) अणु
		अगर (ptr != slr)
			जारी;
		list_del(&ptr->list);
		rc = 0;
		अवरोध;
	पूर्ण
	up_ग_लिखो(&service_level_sem);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_service_level);

अटल व्योम *service_level_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	करोwn_पढ़ो(&service_level_sem);
	वापस seq_list_start(&service_level_list, *pos);
पूर्ण

अटल व्योम *service_level_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	वापस seq_list_next(p, &service_level_list, pos);
पूर्ण

अटल व्योम service_level_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	up_पढ़ो(&service_level_sem);
पूर्ण

अटल पूर्णांक service_level_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा service_level *slr;

	slr = list_entry(p, काष्ठा service_level, list);
	slr->seq_prपूर्णांक(m, slr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations service_level_seq_ops = अणु
	.start		= service_level_start,
	.next		= service_level_next,
	.stop		= service_level_stop,
	.show		= service_level_show
पूर्ण;

अटल व्योम service_level_vm_prपूर्णांक(काष्ठा seq_file *m,
				   काष्ठा service_level *slr)
अणु
	अक्षर *query_buffer, *str;

	query_buffer = kदो_स्मृति(1024, GFP_KERNEL | GFP_DMA);
	अगर (!query_buffer)
		वापस;
	cpcmd("QUERY CPLEVEL", query_buffer, 1024, शून्य);
	str = म_अक्षर(query_buffer, '\n');
	अगर (str)
		*str = 0;
	seq_म_लिखो(m, "VM: %s\n", query_buffer);
	kमुक्त(query_buffer);
पूर्ण

अटल काष्ठा service_level service_level_vm = अणु
	.seq_prपूर्णांक = service_level_vm_prपूर्णांक
पूर्ण;

अटल __init पूर्णांक create_proc_service_level(व्योम)
अणु
	proc_create_seq("service_levels", 0, शून्य, &service_level_seq_ops);
	अगर (MACHINE_IS_VM)
		रेजिस्टर_service_level(&service_level_vm);
	वापस 0;
पूर्ण
subsys_initcall(create_proc_service_level);

/*
 * CPU capability might have changed. Thereक्रमe recalculate loops_per_jअगरfy.
 */
व्योम s390_adjust_jअगरfies(व्योम)
अणु
	काष्ठा sysinfo_1_2_2 *info;
	अचिन्हित दीर्घ capability;
	काष्ठा kernel_fpu fpu;

	info = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!info)
		वापस;

	अगर (stsi(info, 1, 2, 2) == 0) अणु
		/*
		 * Major sigh. The cpu capability encoding is "special".
		 * If the first 9 bits of info->capability are 0 then it
		 * is a 32 bit अचिन्हित पूर्णांकeger in the range 0 .. 2^23.
		 * If the first 9 bits are != 0 then it is a 32 bit भग्न.
		 * In addition a lower value indicates a proportionally
		 * higher cpu capacity. Bogomips are the other way round.
		 * To get to a halfway suitable number we भागide 1e7
		 * by the cpu capability number. Yes, that means a भग्नing
		 * poपूर्णांक भागision ..
		 */
		kernel_fpu_begin(&fpu, KERNEL_FPR);
		यंत्र अस्थिर(
			"	sfpc	%3\n"
			"	l	%0,%1\n"
			"	tmlh	%0,0xff80\n"
			"	jnz	0f\n"
			"	cefbr	%%f2,%0\n"
			"	j	1f\n"
			"0:	le	%%f2,%1\n"
			"1:	cefbr	%%f0,%2\n"
			"	debr	%%f0,%%f2\n"
			"	cgebr	%0,5,%%f0\n"
			: "=&d" (capability)
			: "Q" (info->capability), "d" (10000000), "d" (0)
			: "cc"
			);
		kernel_fpu_end(&fpu, KERNEL_FPR);
	पूर्ण अन्यथा
		/*
		 * Really old machine without stsi block क्रम basic
		 * cpu inक्रमmation. Report 42.0 bogomips.
		 */
		capability = 42;
	loops_per_jअगरfy = capability * (500000/HZ);
	मुक्त_page((अचिन्हित दीर्घ) info);
पूर्ण

/*
 * calibrate the delay loop
 */
व्योम calibrate_delay(व्योम)
अणु
	s390_adjust_jअगरfies();
	/* Prपूर्णांक the good old Bogomips line .. */
	prपूर्णांकk(KERN_DEBUG "Calibrating delay loop (skipped)... "
	       "%lu.%02lu BogoMIPS preset\n", loops_per_jअगरfy/(500000/HZ),
	       (loops_per_jअगरfy/(5000/HZ)) % 100);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा STSI_खाता(fc, s1, s2)						       \
अटल पूर्णांक stsi_खोलो_##fc##_##s1##_##s2(काष्ठा inode *inode, काष्ठा file *file)\
अणु									       \
	file->निजी_data = (व्योम *) get_zeroed_page(GFP_KERNEL);	       \
	अगर (!file->निजी_data)					       \
		वापस -ENOMEM;						       \
	अगर (stsi(file->निजी_data, fc, s1, s2)) अणु			       \
		मुक्त_page((अचिन्हित दीर्घ)file->निजी_data);		       \
		file->निजी_data = शून्य;				       \
		वापस -EACCES;						       \
	पूर्ण								       \
	वापस nonseekable_खोलो(inode, file);				       \
पूर्ण									       \
									       \
अटल स्थिर काष्ठा file_operations stsi_##fc##_##s1##_##s2##_fs_ops = अणु       \
	.खोलो		= stsi_खोलो_##fc##_##s1##_##s2,			       \
	.release	= stsi_release,					       \
	.पढ़ो		= stsi_पढ़ो,					       \
	.llseek		= no_llseek,					       \
पूर्ण;

अटल पूर्णांक stsi_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	मुक्त_page((अचिन्हित दीर्घ)file->निजी_data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार stsi_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, size, ppos, file->निजी_data, PAGE_SIZE);
पूर्ण

STSI_खाता( 1, 1, 1);
STSI_खाता( 1, 2, 1);
STSI_खाता( 1, 2, 2);
STSI_खाता( 2, 2, 1);
STSI_खाता( 2, 2, 2);
STSI_खाता( 3, 2, 2);
STSI_खाता(15, 1, 2);
STSI_खाता(15, 1, 3);
STSI_खाता(15, 1, 4);
STSI_खाता(15, 1, 5);
STSI_खाता(15, 1, 6);

काष्ठा stsi_file अणु
	स्थिर काष्ठा file_operations *fops;
	अक्षर *name;
पूर्ण;

अटल काष्ठा stsi_file stsi_file[] __initdata = अणु
	अणु.fops = &stsi_1_1_1_fs_ops,  .name =  "1_1_1"पूर्ण,
	अणु.fops = &stsi_1_2_1_fs_ops,  .name =  "1_2_1"पूर्ण,
	अणु.fops = &stsi_1_2_2_fs_ops,  .name =  "1_2_2"पूर्ण,
	अणु.fops = &stsi_2_2_1_fs_ops,  .name =  "2_2_1"पूर्ण,
	अणु.fops = &stsi_2_2_2_fs_ops,  .name =  "2_2_2"पूर्ण,
	अणु.fops = &stsi_3_2_2_fs_ops,  .name =  "3_2_2"पूर्ण,
	अणु.fops = &stsi_15_1_2_fs_ops, .name = "15_1_2"पूर्ण,
	अणु.fops = &stsi_15_1_3_fs_ops, .name = "15_1_3"पूर्ण,
	अणु.fops = &stsi_15_1_4_fs_ops, .name = "15_1_4"पूर्ण,
	अणु.fops = &stsi_15_1_5_fs_ops, .name = "15_1_5"पूर्ण,
	अणु.fops = &stsi_15_1_6_fs_ops, .name = "15_1_6"पूर्ण,
पूर्ण;

अटल u8 stsi_0_0_0;

अटल __init पूर्णांक stsi_init_debugfs(व्योम)
अणु
	काष्ठा dentry *stsi_root;
	काष्ठा stsi_file *sf;
	पूर्णांक lvl, i;

	stsi_root = debugfs_create_dir("stsi", arch_debugfs_dir);
	lvl = stsi(शून्य, 0, 0, 0);
	अगर (lvl > 0)
		stsi_0_0_0 = lvl;
	debugfs_create_u8("0_0_0", 0400, stsi_root, &stsi_0_0_0);
	क्रम (i = 0; i < ARRAY_SIZE(stsi_file); i++) अणु
		sf = &stsi_file[i];
		debugfs_create_file(sf->name, 0400, stsi_root, शून्य, sf->fops);
	पूर्ण
	अगर (IS_ENABLED(CONFIG_SCHED_TOPOLOGY) && MACHINE_HAS_TOPOLOGY) अणु
		अक्षर link_to[10];

		प्र_लिखो(link_to, "15_1_%d", topology_mnest_limit());
		debugfs_create_symlink("topology", stsi_root, link_to);
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(stsi_init_debugfs);

#पूर्ण_अगर /* CONFIG_DEBUG_FS */
