<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * palinfo.c
 *
 * Prपूर्णांकs processor specअगरic inक्रमmation reported by PAL.
 * This code is based on specअगरication of PAL as of the
 * Intel IA-64 Architecture Software Developer's Manual v1.0.
 *
 *
 * Copyright (C) 2000-2001, 2003 Hewlett-Packard Co
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 2004 Intel Corporation
 *  Ashok Raj <ashok.raj@पूर्णांकel.com>
 *
 * 05/26/2000	S.Eranian	initial release
 * 08/21/2000	S.Eranian	updated to July 2000 PAL specs
 * 02/05/2001   S.Eranian	fixed module support
 * 10/23/2001	S.Eranian	updated pal_perf_mon_info bug fixes
 * 03/24/2004	Ashok Raj	updated to work with CPU Hotplug
 * 10/26/2006   Russ Anderson	updated processor features to rev 2.2 spec
 */
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/efi.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>

#समावेश <यंत्र/pal.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/smp.h>

MODULE_AUTHOR("Stephane Eranian <eranian@hpl.hp.com>");
MODULE_DESCRIPTION("/proc interface to IA-64 PAL");
MODULE_LICENSE("GPL");

#घोषणा PALINFO_VERSION "0.5"

प्रकार पूर्णांक (*palinfo_func_t)(काष्ठा seq_file *);

प्रकार काष्ठा अणु
	स्थिर अक्षर		*name;		/* name of the proc entry */
	palinfo_func_t		proc_पढ़ो;	/* function to call क्रम पढ़ोing */
	काष्ठा proc_dir_entry	*entry;		/* रेजिस्टरed entry (removal) */
पूर्ण palinfo_entry_t;


/*
 *  A bunch of string array to get pretty prपूर्णांकing
 */

अटल स्थिर अक्षर *cache_types[] = अणु
	"",			/* not used */
	"Instruction",
	"Data",
	"Data/Instruction"	/* unअगरied */
पूर्ण;

अटल स्थिर अक्षर *cache_mattrib[]=अणु
	"WriteThrough",
	"WriteBack",
	"",		/* reserved */
	""		/* reserved */
पूर्ण;

अटल स्थिर अक्षर *cache_st_hपूर्णांकs[]=अणु
	"Temporal, level 1",
	"Reserved",
	"Reserved",
	"Non-temporal, all levels",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
पूर्ण;

अटल स्थिर अक्षर *cache_ld_hपूर्णांकs[]=अणु
	"Temporal, level 1",
	"Non-temporal, level 1",
	"Reserved",
	"Non-temporal, all levels",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
पूर्ण;

अटल स्थिर अक्षर *rse_hपूर्णांकs[]=अणु
	"enforced lazy",
	"eager stores",
	"eager loads",
	"eager loads and stores"
पूर्ण;

#घोषणा RSE_HINTS_COUNT ARRAY_SIZE(rse_hपूर्णांकs)

अटल स्थिर अक्षर *mem_attrib[]=अणु
	"WB",		/* 000 */
	"SW",		/* 001 */
	"010",		/* 010 */
	"011",		/* 011 */
	"UC",		/* 100 */
	"UCE",		/* 101 */
	"WC",		/* 110 */
	"NaTPage"	/* 111 */
पूर्ण;

/*
 * Take a 64bit vector and produces a string such that
 * अगर bit n is set then 2^n in clear text is generated. The adjusपंचांगent
 * to the right unit is also करोne.
 *
 * Input:
 *	- a poपूर्णांकer to a buffer to hold the string
 *	- a 64-bit vector
 * Ouput:
 *	- a poपूर्णांकer to the end of the buffer
 *
 */
अटल व्योम bitvector_process(काष्ठा seq_file *m, u64 vector)
अणु
	पूर्णांक i,j;
	अटल स्थिर अक्षर *units[]=अणु "", "K", "M", "G", "T" पूर्ण;

	क्रम (i=0, j=0; i < 64; i++ , j=i/10) अणु
		अगर (vector & 0x1)
			seq_म_लिखो(m, "%d%s ", 1 << (i-j*10), units[j]);
		vector >>= 1;
	पूर्ण
पूर्ण

/*
 * Take a 64bit vector and produces a string such that
 * अगर bit n is set then रेजिस्टर n is present. The function
 * takes पूर्णांकo account consecutive रेजिस्टरs and prपूर्णांकs out ranges.
 *
 * Input:
 *	- a poपूर्णांकer to a buffer to hold the string
 *	- a 64-bit vector
 * Ouput:
 *	- a poपूर्णांकer to the end of the buffer
 *
 */
अटल व्योम bitरेजिस्टर_process(काष्ठा seq_file *m, u64 *reg_info, पूर्णांक max)
अणु
	पूर्णांक i, begin, skip = 0;
	u64 value = reg_info[0];

	value >>= i = begin = ffs(value) - 1;

	क्रम(; i < max; i++ ) अणु

		अगर (i != 0 && (i%64) == 0) value = *++reg_info;

		अगर ((value & 0x1) == 0 && skip == 0) अणु
			अगर (begin  <= i - 2)
				seq_म_लिखो(m, "%d-%d ", begin, i-1);
			अन्यथा
				seq_म_लिखो(m, "%d ", i-1);
			skip  = 1;
			begin = -1;
		पूर्ण अन्यथा अगर ((value & 0x1) && skip == 1) अणु
			skip = 0;
			begin = i;
		पूर्ण
		value >>=1;
	पूर्ण
	अगर (begin > -1) अणु
		अगर (begin < 127)
			seq_म_लिखो(m, "%d-127", begin);
		अन्यथा
			seq_माला_दो(m, "127");
	पूर्ण
पूर्ण

अटल पूर्णांक घातer_info(काष्ठा seq_file *m)
अणु
	s64 status;
	u64 halt_info_buffer[8];
	pal_घातer_mgmt_info_u_t *halt_info =(pal_घातer_mgmt_info_u_t *)halt_info_buffer;
	पूर्णांक i;

	status = ia64_pal_halt_info(halt_info);
	अगर (status != 0) वापस 0;

	क्रम (i=0; i < 8 ; i++ ) अणु
		अगर (halt_info[i].pal_घातer_mgmt_info_s.im == 1) अणु
			seq_म_लिखो(m,
				   "Power level %d:\n"
				   "\tentry_latency       : %d cycles\n"
				   "\texit_latency        : %d cycles\n"
				   "\tpower consumption   : %d mW\n"
				   "\tCache+TLB coherency : %s\n", i,
				   halt_info[i].pal_घातer_mgmt_info_s.entry_latency,
				   halt_info[i].pal_घातer_mgmt_info_s.निकास_latency,
				   halt_info[i].pal_घातer_mgmt_info_s.घातer_consumption,
				   halt_info[i].pal_घातer_mgmt_info_s.co ? "Yes" : "No");
		पूर्ण अन्यथा अणु
			seq_म_लिखो(m,"Power level %d: not implemented\n", i);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cache_info(काष्ठा seq_file *m)
अणु
	अचिन्हित दीर्घ i, levels, unique_caches;
	pal_cache_config_info_t cci;
	पूर्णांक j, k;
	दीर्घ status;

	अगर ((status = ia64_pal_cache_summary(&levels, &unique_caches)) != 0) अणु
		prपूर्णांकk(KERN_ERR "ia64_pal_cache_summary=%ld\n", status);
		वापस 0;
	पूर्ण

	seq_म_लिखो(m, "Cache levels  : %ld\nUnique caches : %ld\n\n",
		   levels, unique_caches);

	क्रम (i=0; i < levels; i++) अणु
		क्रम (j=2; j >0 ; j--) अणु
			/* even without unअगरication some level may not be present */
			अगर ((status=ia64_pal_cache_config_info(i,j, &cci)) != 0)
				जारी;

			seq_म_लिखो(m,
				   "%s Cache level %lu:\n"
				   "\tSize           : %u bytes\n"
				   "\tAttributes     : ",
				   cache_types[j+cci.pcci_unअगरied], i+1,
				   cci.pcci_cache_size);

			अगर (cci.pcci_unअगरied)
				seq_माला_दो(m, "Unified ");

			seq_म_लिखो(m, "%s\n", cache_mattrib[cci.pcci_cache_attr]);

			seq_म_लिखो(m,
				   "\tAssociativity  : %d\n"
				   "\tLine size      : %d bytes\n"
				   "\tStride         : %d bytes\n",
				   cci.pcci_assoc,
				   1<<cci.pcci_line_size,
				   1<<cci.pcci_stride);
			अगर (j == 1)
				seq_माला_दो(m, "\tStore latency  : N/A\n");
			अन्यथा
				seq_म_लिखो(m, "\tStore latency  : %d cycle(s)\n",
					   cci.pcci_st_latency);

			seq_म_लिखो(m,
				   "\tLoad latency   : %d cycle(s)\n"
				   "\tStore hints    : ", cci.pcci_ld_latency);

			क्रम(k=0; k < 8; k++ ) अणु
				अगर ( cci.pcci_st_hपूर्णांकs & 0x1)
					seq_म_लिखो(m, "[%s]", cache_st_hपूर्णांकs[k]);
				cci.pcci_st_hपूर्णांकs >>=1;
			पूर्ण
			seq_माला_दो(m, "\n\tLoad hints     : ");

			क्रम(k=0; k < 8; k++ ) अणु
				अगर (cci.pcci_ld_hपूर्णांकs & 0x1)
					seq_म_लिखो(m, "[%s]", cache_ld_hपूर्णांकs[k]);
				cci.pcci_ld_hपूर्णांकs >>=1;
			पूर्ण
			seq_म_लिखो(m,
				   "\n\tAlias boundary : %d byte(s)\n"
				   "\tTag LSB        : %d\n"
				   "\tTag MSB        : %d\n",
				   1<<cci.pcci_alias_boundary, cci.pcci_tag_lsb,
				   cci.pcci_tag_msb);

			/* when unअगरied, data(j=2) is enough */
			अगर (cci.pcci_unअगरied)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक vm_info(काष्ठा seq_file *m)
अणु
	u64 tr_pages =0, vw_pages=0, tc_pages;
	u64 attrib;
	pal_vm_info_1_u_t vm_info_1;
	pal_vm_info_2_u_t vm_info_2;
	pal_tc_info_u_t	tc_info;
	ia64_ptce_info_t ptce;
	स्थिर अक्षर *sep;
	पूर्णांक i, j;
	दीर्घ status;

	अगर ((status = ia64_pal_vm_summary(&vm_info_1, &vm_info_2)) !=0) अणु
		prपूर्णांकk(KERN_ERR "ia64_pal_vm_summary=%ld\n", status);
	पूर्ण अन्यथा अणु

		seq_म_लिखो(m,
		     "Physical Address Space         : %d bits\n"
		     "Virtual Address Space          : %d bits\n"
		     "Protection Key Registers(PKR)  : %d\n"
		     "Implemented bits in PKR.key    : %d\n"
		     "Hash Tag ID                    : 0x%x\n"
		     "Size of RR.rid                 : %d\n"
		     "Max Purges                     : ",
		     vm_info_1.pal_vm_info_1_s.phys_add_size,
		     vm_info_2.pal_vm_info_2_s.impl_va_msb+1,
		     vm_info_1.pal_vm_info_1_s.max_pkr+1,
		     vm_info_1.pal_vm_info_1_s.key_size,
		     vm_info_1.pal_vm_info_1_s.hash_tag_id,
		     vm_info_2.pal_vm_info_2_s.rid_size);
		अगर (vm_info_2.pal_vm_info_2_s.max_purges == PAL_MAX_PURGES)
			seq_माला_दो(m, "unlimited\n");
		अन्यथा
			seq_म_लिखो(m, "%d\n",
		     		vm_info_2.pal_vm_info_2_s.max_purges ?
				vm_info_2.pal_vm_info_2_s.max_purges : 1);
	पूर्ण

	अगर (ia64_pal_mem_attrib(&attrib) == 0) अणु
		seq_माला_दो(m, "Supported memory attributes    : ");
		sep = "";
		क्रम (i = 0; i < 8; i++) अणु
			अगर (attrib & (1 << i)) अणु
				seq_म_लिखो(m, "%s%s", sep, mem_attrib[i]);
				sep = ", ";
			पूर्ण
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण

	अगर ((status = ia64_pal_vm_page_size(&tr_pages, &vw_pages)) !=0) अणु
		prपूर्णांकk(KERN_ERR "ia64_pal_vm_page_size=%ld\n", status);
	पूर्ण अन्यथा अणु

		seq_म_लिखो(m,
			   "\nTLB walker                     : %simplemented\n"
			   "Number of DTR                  : %d\n"
			   "Number of ITR                  : %d\n"
			   "TLB insertable page sizes      : ",
			   vm_info_1.pal_vm_info_1_s.vw ? "" : "not ",
			   vm_info_1.pal_vm_info_1_s.max_dtr_entry+1,
			   vm_info_1.pal_vm_info_1_s.max_itr_entry+1);

		bitvector_process(m, tr_pages);

		seq_माला_दो(m, "\nTLB purgeable page sizes       : ");

		bitvector_process(m, vw_pages);
	पूर्ण

	अगर ((status = ia64_get_ptce(&ptce)) != 0) अणु
		prपूर्णांकk(KERN_ERR "ia64_get_ptce=%ld\n", status);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m,
		     "\nPurge base address             : 0x%016lx\n"
		     "Purge outer loop count         : %d\n"
		     "Purge inner loop count         : %d\n"
		     "Purge outer loop stride        : %d\n"
		     "Purge inner loop stride        : %d\n",
		     ptce.base, ptce.count[0], ptce.count[1],
		     ptce.stride[0], ptce.stride[1]);

		seq_म_लिखो(m,
		     "TC Levels                      : %d\n"
		     "Unique TC(s)                   : %d\n",
		     vm_info_1.pal_vm_info_1_s.num_tc_levels,
		     vm_info_1.pal_vm_info_1_s.max_unique_tcs);

		क्रम(i=0; i < vm_info_1.pal_vm_info_1_s.num_tc_levels; i++) अणु
			क्रम (j=2; j>0 ; j--) अणु
				tc_pages = 0; /* just in हाल */

				/* even without unअगरication, some levels may not be present */
				अगर ((status=ia64_pal_vm_info(i,j, &tc_info, &tc_pages)) != 0)
					जारी;

				seq_म_लिखो(m,
				     "\n%s Translation Cache Level %d:\n"
				     "\tHash sets           : %d\n"
				     "\tAssociativity       : %d\n"
				     "\tNumber of entries   : %d\n"
				     "\tFlags               : ",
				     cache_types[j+tc_info.tc_unअगरied], i+1,
				     tc_info.tc_num_sets,
				     tc_info.tc_associativity,
				     tc_info.tc_num_entries);

				अगर (tc_info.tc_pf)
					seq_माला_दो(m, "PreferredPageSizeOptimized ");
				अगर (tc_info.tc_unअगरied)
					seq_माला_दो(m, "Unified ");
				अगर (tc_info.tc_reduce_tr)
					seq_माला_दो(m, "TCReduction");

				seq_माला_दो(m, "\n\tSupported page sizes: ");

				bitvector_process(m, tc_pages);

				/* when unअगरied date (j=2) is enough */
				अगर (tc_info.tc_unअगरied)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण


अटल पूर्णांक रेजिस्टर_info(काष्ठा seq_file *m)
अणु
	u64 reg_info[2];
	u64 info;
	अचिन्हित दीर्घ phys_stacked;
	pal_hपूर्णांकs_u_t hपूर्णांकs;
	अचिन्हित दीर्घ iregs, dregs;
	अटल स्थिर अक्षर * स्थिर info_type[] = अणु
		"Implemented AR(s)",
		"AR(s) with read side-effects",
		"Implemented CR(s)",
		"CR(s) with read side-effects",
	पूर्ण;

	क्रम(info=0; info < 4; info++) अणु
		अगर (ia64_pal_रेजिस्टर_info(info, &reg_info[0], &reg_info[1]) != 0)
			वापस 0;
		seq_म_लिखो(m, "%-32s : ", info_type[info]);
		bitरेजिस्टर_process(m, reg_info, 128);
		seq_अ_दो(m, '\n');
	पूर्ण

	अगर (ia64_pal_rse_info(&phys_stacked, &hपूर्णांकs) == 0)
		seq_म_लिखो(m,
			   "RSE stacked physical registers   : %ld\n"
			   "RSE load/store hints             : %ld (%s)\n",
			   phys_stacked, hपूर्णांकs.ph_data,
			   hपूर्णांकs.ph_data < RSE_HINTS_COUNT ? rse_hपूर्णांकs[hपूर्णांकs.ph_data]: "(??)");

	अगर (ia64_pal_debug_info(&iregs, &dregs))
		वापस 0;

	seq_म_लिखो(m,
		   "Instruction debug register pairs : %ld\n"
		   "Data debug register pairs        : %ld\n", iregs, dregs);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *स्थिर proc_features_0[]=अणु		/* Feature set 0 */
	शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,
	शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य, शून्य,शून्य,
	शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,
	शून्य,शून्य,शून्य,शून्य,शून्य, शून्य,शून्य,शून्य,शून्य,
	"Unimplemented instruction address fault",
	"INIT, PMI, and LINT pins",
	"Simple unimplemented instr addresses",
	"Variable P-state performance",
	"Virtual machine features implemented",
	"XIP,XPSR,XFS implemented",
	"XR1-XR3 implemented",
	"Disable dynamic predicate prediction",
	"Disable processor physical number",
	"Disable dynamic data cache prefetch",
	"Disable dynamic inst cache prefetch",
	"Disable dynamic branch prediction",
	शून्य, शून्य, शून्य, शून्य,
	"Disable P-states",
	"Enable MCA on Data Poisoning",
	"Enable vmsw instruction",
	"Enable extern environmental notification",
	"Disable BINIT on processor time-out",
	"Disable dynamic power management (DPM)",
	"Disable coherency",
	"Disable cache",
	"Enable CMCI promotion",
	"Enable MCA to BINIT promotion",
	"Enable MCA promotion",
	"Enable BERR promotion"
पूर्ण;

अटल स्थिर अक्षर *स्थिर proc_features_16[]=अणु		/* Feature set 16 */
	"Disable ETM",
	"Enable ETM",
	"Enable MCA on half-way timer",
	"Enable snoop WC",
	शून्य,
	"Enable Fast Deferral",
	"Disable MCA on memory aliasing",
	"Enable RSB",
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	"DP system processor",
	"Low Voltage",
	"HT supported",
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य
पूर्ण;

अटल स्थिर अक्षर *स्थिर *स्थिर proc_features[]=अणु
	proc_features_0,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य,
	proc_features_16,
	शून्य, शून्य, शून्य, शून्य,
पूर्ण;

अटल व्योम feature_set_info(काष्ठा seq_file *m, u64 avail, u64 status, u64 control,
			     अचिन्हित दीर्घ set)
अणु
	स्थिर अक्षर *स्थिर *vf, *स्थिर *v;
	पूर्णांक i;

	vf = v = proc_features[set];
	क्रम(i=0; i < 64; i++, avail >>=1, status >>=1, control >>=1) अणु

		अगर (!(control))		/* No reमुख्यing bits set */
			अवरोध;
		अगर (!(avail & 0x1))	/* Prपूर्णांक only bits that are available */
			जारी;
		अगर (vf)
			v = vf + i;
		अगर ( v && *v ) अणु
			seq_म_लिखो(m, "%-40s : %s %s\n", *v,
				avail & 0x1 ? (status & 0x1 ?
					      "On " : "Off"): "",
				avail & 0x1 ? (control & 0x1 ?
						"Ctrl" : "NoCtrl"): "");
		पूर्ण अन्यथा अणु
			seq_म_लिखो(m, "Feature set %2ld bit %2d\t\t\t"
					" : %s %s\n",
				set, i,
				avail & 0x1 ? (status & 0x1 ?
						"On " : "Off"): "",
				avail & 0x1 ? (control & 0x1 ?
						"Ctrl" : "NoCtrl"): "");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक processor_info(काष्ठा seq_file *m)
अणु
	u64 avail=1, status=1, control=1, feature_set=0;
	s64 ret;

	करो अणु
		ret = ia64_pal_proc_get_features(&avail, &status, &control,
						feature_set);
		अगर (ret < 0)
			वापस 0;

		अगर (ret == 1) अणु
			feature_set++;
			जारी;
		पूर्ण

		feature_set_info(m, avail, status, control, feature_set);
		feature_set++;
	पूर्ण जबतक(1);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *स्थिर bus_features[]=अणु
	शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,
	शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य, शून्य,शून्य,
	शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,शून्य,
	शून्य,शून्य,
	"Request  Bus Parking",
	"Bus Lock Mask",
	"Enable Half Transfer",
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य,
	"Enable Cache Line Repl. Shared",
	"Enable Cache Line Repl. Exclusive",
	"Disable Transaction Queuing",
	"Disable Response Error Checking",
	"Disable Bus Error Checking",
	"Disable Bus Requester Internal Error Signalling",
	"Disable Bus Requester Error Signalling",
	"Disable Bus Initialization Event Checking",
	"Disable Bus Initialization Event Signalling",
	"Disable Bus Address Error Checking",
	"Disable Bus Address Error Signalling",
	"Disable Bus Data Error Checking"
पूर्ण;


अटल पूर्णांक bus_info(काष्ठा seq_file *m)
अणु
	स्थिर अक्षर *स्थिर *v = bus_features;
	pal_bus_features_u_t av, st, ct;
	u64 avail, status, control;
	पूर्णांक i;
	s64 ret;

	अगर ((ret=ia64_pal_bus_get_features(&av, &st, &ct)) != 0)
		वापस 0;

	avail   = av.pal_bus_features_val;
	status  = st.pal_bus_features_val;
	control = ct.pal_bus_features_val;

	क्रम(i=0; i < 64; i++, v++, avail >>=1, status >>=1, control >>=1) अणु
		अगर ( ! *v )
			जारी;
		seq_म_लिखो(m, "%-48s : %s%s %s\n", *v,
			   avail & 0x1 ? "" : "NotImpl",
			   avail & 0x1 ? (status  & 0x1 ? "On" : "Off"): "",
			   avail & 0x1 ? (control & 0x1 ? "Ctrl" : "NoCtrl"): "");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक version_info(काष्ठा seq_file *m)
अणु
	pal_version_u_t min_ver, cur_ver;

	अगर (ia64_pal_version(&min_ver, &cur_ver) != 0)
		वापस 0;

	seq_म_लिखो(m,
		   "PAL_vendor : 0x%02x (min=0x%02x)\n"
		   "PAL_A      : %02x.%02x (min=%02x.%02x)\n"
		   "PAL_B      : %02x.%02x (min=%02x.%02x)\n",
		   cur_ver.pal_version_s.pv_pal_venकरोr,
		   min_ver.pal_version_s.pv_pal_venकरोr,
		   cur_ver.pal_version_s.pv_pal_a_model,
		   cur_ver.pal_version_s.pv_pal_a_rev,
		   min_ver.pal_version_s.pv_pal_a_model,
		   min_ver.pal_version_s.pv_pal_a_rev,
		   cur_ver.pal_version_s.pv_pal_b_model,
		   cur_ver.pal_version_s.pv_pal_b_rev,
		   min_ver.pal_version_s.pv_pal_b_model,
		   min_ver.pal_version_s.pv_pal_b_rev);
	वापस 0;
पूर्ण

अटल पूर्णांक frequency_info(काष्ठा seq_file *m)
अणु
	काष्ठा pal_freq_ratio proc, itc, bus;
	अचिन्हित दीर्घ base;

	अगर (ia64_pal_freq_base(&base) == -1)
		seq_माला_दो(m, "Output clock            : not implemented\n");
	अन्यथा
		seq_म_लिखो(m, "Output clock            : %ld ticks/s\n", base);

	अगर (ia64_pal_freq_ratios(&proc, &bus, &itc) != 0) वापस 0;

	seq_म_लिखो(m,
		     "Processor/Clock ratio   : %d/%d\n"
		     "Bus/Clock ratio         : %d/%d\n"
		     "ITC/Clock ratio         : %d/%d\n",
		     proc.num, proc.den, bus.num, bus.den, itc.num, itc.den);
	वापस 0;
पूर्ण

अटल पूर्णांक tr_info(काष्ठा seq_file *m)
अणु
	दीर्घ status;
	pal_tr_valid_u_t tr_valid;
	u64 tr_buffer[4];
	pal_vm_info_1_u_t vm_info_1;
	pal_vm_info_2_u_t vm_info_2;
	अचिन्हित दीर्घ i, j;
	अचिन्हित दीर्घ max[3], pgm;
	काष्ठा अगरa_reg अणु
		अचिन्हित दीर्घ valid:1;
		अचिन्हित दीर्घ ig:11;
		अचिन्हित दीर्घ vpn:52;
	पूर्ण *अगरa_reg;
	काष्ठा itir_reg अणु
		अचिन्हित दीर्घ rv1:2;
		अचिन्हित दीर्घ ps:6;
		अचिन्हित दीर्घ key:24;
		अचिन्हित दीर्घ rv2:32;
	पूर्ण *itir_reg;
	काष्ठा gr_reg अणु
		अचिन्हित दीर्घ p:1;
		अचिन्हित दीर्घ rv1:1;
		अचिन्हित दीर्घ ma:3;
		अचिन्हित दीर्घ a:1;
		अचिन्हित दीर्घ d:1;
		अचिन्हित दीर्घ pl:2;
		अचिन्हित दीर्घ ar:3;
		अचिन्हित दीर्घ ppn:38;
		अचिन्हित दीर्घ rv2:2;
		अचिन्हित दीर्घ ed:1;
		अचिन्हित दीर्घ ig:11;
	पूर्ण *gr_reg;
	काष्ठा rid_reg अणु
		अचिन्हित दीर्घ ig1:1;
		अचिन्हित दीर्घ rv1:1;
		अचिन्हित दीर्घ ig2:6;
		अचिन्हित दीर्घ rid:24;
		अचिन्हित दीर्घ rv2:32;
	पूर्ण *rid_reg;

	अगर ((status = ia64_pal_vm_summary(&vm_info_1, &vm_info_2)) !=0) अणु
		prपूर्णांकk(KERN_ERR "ia64_pal_vm_summary=%ld\n", status);
		वापस 0;
	पूर्ण
	max[0] = vm_info_1.pal_vm_info_1_s.max_itr_entry+1;
	max[1] = vm_info_1.pal_vm_info_1_s.max_dtr_entry+1;

	क्रम (i=0; i < 2; i++ ) अणु
		क्रम (j=0; j < max[i]; j++) अणु

		status = ia64_pal_tr_पढ़ो(j, i, tr_buffer, &tr_valid);
		अगर (status != 0) अणु
			prपूर्णांकk(KERN_ERR "palinfo: pal call failed on tr[%lu:%lu]=%ld\n",
			       i, j, status);
			जारी;
		पूर्ण

		अगरa_reg  = (काष्ठा अगरa_reg *)&tr_buffer[2];

		अगर (अगरa_reg->valid == 0)
			जारी;

		gr_reg   = (काष्ठा gr_reg *)tr_buffer;
		itir_reg = (काष्ठा itir_reg *)&tr_buffer[1];
		rid_reg  = (काष्ठा rid_reg *)&tr_buffer[3];

		pgm	 = -1 << (itir_reg->ps - 12);
		seq_म_लिखो(m,
			   "%cTR%lu: av=%d pv=%d dv=%d mv=%d\n"
			   "\tppn  : 0x%lx\n"
			   "\tvpn  : 0x%lx\n"
			   "\tps   : ",
			   "ID"[i], j,
			   tr_valid.pal_tr_valid_s.access_rights_valid,
			   tr_valid.pal_tr_valid_s.priv_level_valid,
			   tr_valid.pal_tr_valid_s.dirty_bit_valid,
			   tr_valid.pal_tr_valid_s.mem_attr_valid,
			   (gr_reg->ppn & pgm)<< 12, (अगरa_reg->vpn & pgm)<< 12);

		bitvector_process(m, 1<< itir_reg->ps);

		seq_म_लिखो(m,
			   "\n\tpl   : %d\n"
			   "\tar   : %d\n"
			   "\trid  : %x\n"
			   "\tp    : %d\n"
			   "\tma   : %d\n"
			   "\td    : %d\n",
			   gr_reg->pl, gr_reg->ar, rid_reg->rid, gr_reg->p, gr_reg->ma,
			   gr_reg->d);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण



/*
 * List अणुname,functionपूर्ण pairs क्रम every entry in /proc/palinfo/cpu*
 */
अटल स्थिर palinfo_entry_t palinfo_entries[]=अणु
	अणु "version_info",	version_info, पूर्ण,
	अणु "vm_info",		vm_info, पूर्ण,
	अणु "cache_info",		cache_info, पूर्ण,
	अणु "power_info",		घातer_info, पूर्ण,
	अणु "register_info",	रेजिस्टर_info, पूर्ण,
	अणु "processor_info",	processor_info, पूर्ण,
	अणु "frequency_info",	frequency_info, पूर्ण,
	अणु "bus_info",		bus_info पूर्ण,
	अणु "tr_info",		tr_info, पूर्ण
पूर्ण;

#घोषणा NR_PALINFO_ENTRIES	(पूर्णांक) ARRAY_SIZE(palinfo_entries)

अटल काष्ठा proc_dir_entry *palinfo_dir;

/*
 * This data काष्ठाure is used to pass which cpu,function is being requested
 * It must fit in a 64bit quantity to be passed to the proc callback routine
 *
 * In SMP mode, when we get a request क्रम another CPU, we must call that
 * other CPU using IPI and रुको क्रम the result beक्रमe वापसing.
 */
प्रकार जोड़ अणु
	u64 value;
	काष्ठा अणु
		अचिन्हित	req_cpu: 32;	/* क्रम which CPU this info is */
		अचिन्हित	func_id: 32;	/* which function is requested */
	पूर्ण pal_func_cpu;
पूर्ण pal_func_cpu_u_t;

#घोषणा req_cpu	pal_func_cpu.req_cpu
#घोषणा func_id pal_func_cpu.func_id

#अगर_घोषित CONFIG_SMP

/*
 * used to hold inक्रमmation about final function to call
 */
प्रकार काष्ठा अणु
	palinfo_func_t	func;	/* poपूर्णांकer to function to call */
	काष्ठा seq_file *m;	/* buffer to store results */
	पूर्णांक		ret;	/* वापस value from call */
पूर्ण palinfo_smp_data_t;


/*
 * this function करोes the actual final call and he called
 * from the smp code, i.e., this is the palinfo callback routine
 */
अटल व्योम
palinfo_smp_call(व्योम *info)
अणु
	palinfo_smp_data_t *data = (palinfo_smp_data_t *)info;
	data->ret = (*data->func)(data->m);
पूर्ण

/*
 * function called to trigger the IPI, we need to access a remote CPU
 * Return:
 *	0 : error or nothing to output
 *	otherwise how many bytes in the "page" buffer were written
 */
अटल
पूर्णांक palinfo_handle_smp(काष्ठा seq_file *m, pal_func_cpu_u_t *f)
अणु
	palinfo_smp_data_t ptr;
	पूर्णांक ret;

	ptr.func = palinfo_entries[f->func_id].proc_पढ़ो;
	ptr.m = m;
	ptr.ret  = 0; /* just in हाल */


	/* will send IPI to other CPU and रुको क्रम completion of remote call */
	अगर ((ret=smp_call_function_single(f->req_cpu, palinfo_smp_call, &ptr, 1))) अणु
		prपूर्णांकk(KERN_ERR "palinfo: remote CPU call from %d to %d on function %d: "
		       "error %d\n", smp_processor_id(), f->req_cpu, f->func_id, ret);
		वापस 0;
	पूर्ण
	वापस ptr.ret;
पूर्ण
#अन्यथा /* ! CONFIG_SMP */
अटल
पूर्णांक palinfo_handle_smp(काष्ठा seq_file *m, pal_func_cpu_u_t *f)
अणु
	prपूर्णांकk(KERN_ERR "palinfo: should not be called with non SMP kernel\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Entry poपूर्णांक routine: all calls go through this function
 */
अटल पूर्णांक proc_palinfo_show(काष्ठा seq_file *m, व्योम *v)
अणु
	pal_func_cpu_u_t *f = (pal_func_cpu_u_t *)&m->निजी;

	/*
	 * in SMP mode, we may need to call another CPU to get correct
	 * inक्रमmation. PAL, by definition, is processor specअगरic
	 */
	अगर (f->req_cpu == get_cpu())
		(*palinfo_entries[f->func_id].proc_पढ़ो)(m);
	अन्यथा
		palinfo_handle_smp(m, f);

	put_cpu();
	वापस 0;
पूर्ण

अटल पूर्णांक palinfo_add_proc(अचिन्हित पूर्णांक cpu)
अणु
	pal_func_cpu_u_t f;
	काष्ठा proc_dir_entry *cpu_dir;
	पूर्णांक j;
	अक्षर cpustr[3+4+1];	/* cpu numbers are up to 4095 on itanic */
	प्र_लिखो(cpustr, "cpu%d", cpu);

	cpu_dir = proc_सूची_गढ़ो(cpustr, palinfo_dir);
	अगर (!cpu_dir)
		वापस -EINVAL;

	f.req_cpu = cpu;

	क्रम (j=0; j < NR_PALINFO_ENTRIES; j++) अणु
		f.func_id = j;
		proc_create_single_data(palinfo_entries[j].name, 0, cpu_dir,
				proc_palinfo_show, (व्योम *)f.value);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक palinfo_del_proc(अचिन्हित पूर्णांक hcpu)
अणु
	अक्षर cpustr[3+4+1];	/* cpu numbers are up to 4095 on itanic */

	प्र_लिखो(cpustr, "cpu%d", hcpu);
	हटाओ_proc_subtree(cpustr, palinfo_dir);
	वापस 0;
पूर्ण

अटल क्रमागत cpuhp_state hp_online;

अटल पूर्णांक __init palinfo_init(व्योम)
अणु
	पूर्णांक i = 0;

	prपूर्णांकk(KERN_INFO "PAL Information Facility v%s\n", PALINFO_VERSION);
	palinfo_dir = proc_सूची_गढ़ो("pal", शून्य);
	अगर (!palinfo_dir)
		वापस -ENOMEM;

	i = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "ia64/palinfo:online",
			      palinfo_add_proc, palinfo_del_proc);
	अगर (i < 0) अणु
		हटाओ_proc_subtree("pal", शून्य);
		वापस i;
	पूर्ण
	hp_online = i;
	वापस 0;
पूर्ण

अटल व्योम __निकास palinfo_निकास(व्योम)
अणु
	cpuhp_हटाओ_state(hp_online);
	हटाओ_proc_subtree("pal", शून्य);
पूर्ण

module_init(palinfo_init);
module_निकास(palinfo_निकास);
