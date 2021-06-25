<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  (c) 2003-2006 Advanced Micro Devices, Inc.
 */

काष्ठा घातernow_k8_data अणु
	अचिन्हित पूर्णांक cpu;

	u32 numps;  /* number of p-states */
	u32 batps;  /* number of p-states supported on battery */

	/* these values are स्थिरant when the PSB is used to determine
	 * vid/fid pairings, but are modअगरied during the ->target() call
	 * when ACPI is used */
	u32 rvo;     /* ramp voltage offset */
	u32 irt;     /* isochronous relief समय */
	u32 vidmvs;  /* usable value calculated from mvs */
	u32 vstable; /* voltage stabilization समय, units 20 us */
	u32 plllock; /* pll lock समय, units 1 us */
	u32 exttype; /* extended पूर्णांकerface = 1 */

	/* keep track of the current fid / vid or pstate */
	u32 currvid;
	u32 currfid;

	/* the घातernow_table includes all frequency and vid/fid pairings:
	 * fid are the lower 8 bits of the index, vid are the upper 8 bits.
	 * frequency is in kHz */
	काष्ठा cpufreq_frequency_table  *घातernow_table;

	/* the acpi table needs to be kept. it's only available अगर ACPI was
	 * used to determine valid frequency/vid/fid states */
	काष्ठा acpi_processor_perक्रमmance acpi_data;

	/* we need to keep track of associated cores, but let cpufreq
	 * handle hotplug events - so just poपूर्णांक at cpufreq pol->cpus
	 * काष्ठाure */
	काष्ठा cpumask *available_cores;
पूर्ण;

/* processor's cpuid inकाष्ठाion support */
#घोषणा CPUID_PROCESSOR_SIGNATURE	1	/* function 1 */
#घोषणा CPUID_XFAM			0x0ff00000	/* extended family */
#घोषणा CPUID_XFAM_K8			0
#घोषणा CPUID_XMOD			0x000f0000	/* extended model */
#घोषणा CPUID_XMOD_REV_MASK		0x000c0000
#घोषणा CPUID_XFAM_10H			0x00100000	/* family 0x10 */
#घोषणा CPUID_USE_XFAM_XMOD		0x00000f00
#घोषणा CPUID_GET_MAX_CAPABILITIES	0x80000000
#घोषणा CPUID_FREQ_VOLT_CAPABILITIES	0x80000007
#घोषणा P_STATE_TRANSITION_CAPABLE	6

/* Model Specअगरic Registers क्रम p-state transitions. MSRs are 64-bit. For     */
/* ग_लिखोs (wrmsr - opcode 0f 30), the रेजिस्टर number is placed in ecx, and   */
/* the value to ग_लिखो is placed in edx:eax. For पढ़ोs (rdmsr - opcode 0f 32), */
/* the रेजिस्टर number is placed in ecx, and the data is वापसed in edx:eax. */

#घोषणा MSR_FIDVID_CTL      0xc0010041
#घोषणा MSR_FIDVID_STATUS   0xc0010042

/* Field definitions within the FID VID Low Control MSR : */
#घोषणा MSR_C_LO_INIT_FID_VID     0x00010000
#घोषणा MSR_C_LO_NEW_VID          0x00003f00
#घोषणा MSR_C_LO_NEW_FID          0x0000003f
#घोषणा MSR_C_LO_VID_SHIFT        8

/* Field definitions within the FID VID High Control MSR : */
#घोषणा MSR_C_HI_STP_GNT_TO	  0x000fffff

/* Field definitions within the FID VID Low Status MSR : */
#घोषणा MSR_S_LO_CHANGE_PENDING   0x80000000   /* cleared when completed */
#घोषणा MSR_S_LO_MAX_RAMP_VID     0x3f000000
#घोषणा MSR_S_LO_MAX_FID          0x003f0000
#घोषणा MSR_S_LO_START_FID        0x00003f00
#घोषणा MSR_S_LO_CURRENT_FID      0x0000003f

/* Field definitions within the FID VID High Status MSR : */
#घोषणा MSR_S_HI_MIN_WORKING_VID  0x3f000000
#घोषणा MSR_S_HI_MAX_WORKING_VID  0x003f0000
#घोषणा MSR_S_HI_START_VID        0x00003f00
#घोषणा MSR_S_HI_CURRENT_VID      0x0000003f
#घोषणा MSR_C_HI_STP_GNT_BENIGN	  0x00000001

/*
 * There are restrictions frequencies have to follow:
 * - only 1 entry in the low fid table ( <=1.4GHz )
 * - lowest entry in the high fid table must be >= 2 * the entry in the
 *   low fid table
 * - lowest entry in the high fid table must be a <= 200MHz + 2 * the entry
 *   in the low fid table
 * - the parts can only step at <= 200 MHz पूर्णांकervals, odd fid values are
 *   supported in revision G and later revisions.
 * - lowest frequency must be >= पूर्णांकerprocessor hypertransport link speed
 *   (only applies to MP प्रणालीs obviously)
 */

/* fids (frequency identअगरiers) are arranged in 2 tables - lo and hi */
#घोषणा LO_FID_TABLE_TOP     7	/* fid values marking the boundary    */
#घोषणा HI_FID_TABLE_BOTTOM  8	/* between the low and high tables    */

#घोषणा LO_VCOFREQ_TABLE_TOP    1400	/* corresponding vco frequency values */
#घोषणा HI_VCOFREQ_TABLE_BOTTOM 1600

#घोषणा MIN_FREQ_RESOLUTION  200 /* fids jump by 2 matching freq jumps by 200 */

#घोषणा MAX_FID 0x2a	/* Spec only gives FID values as far as 5 GHz */
#घोषणा LEAST_VID 0x3e	/* Lowest (numerically highest) useful vid value */

#घोषणा MIN_FREQ 800	/* Min and max freqs, per spec */
#घोषणा MAX_FREQ 5000

#घोषणा INVALID_FID_MASK 0xffffffc0  /* not a valid fid अगर these bits are set */
#घोषणा INVALID_VID_MASK 0xffffffc0  /* not a valid vid अगर these bits are set */

#घोषणा VID_OFF 0x3f

#घोषणा STOP_GRANT_5NS 1 /* min poss memory access latency क्रम voltage change */

#घोषणा PLL_LOCK_CONVERSION (1000/5) /* ms to ns, then भागide by घड़ी period */

#घोषणा MAXIMUM_VID_STEPS 1  /* Current cpus only allow a single step of 25mV */
#घोषणा VST_UNITS_20US 20   /* Voltage Stabilization Time is in units of 20us */

/*
 * Most values of पूर्णांकerest are encoded in a single field of the _PSS
 * entries: the "control" value.
 */

#घोषणा IRT_SHIFT      30
#घोषणा RVO_SHIFT      28
#घोषणा EXT_TYPE_SHIFT 27
#घोषणा PLL_L_SHIFT    20
#घोषणा MVS_SHIFT      18
#घोषणा VST_SHIFT      11
#घोषणा VID_SHIFT       6
#घोषणा IRT_MASK        3
#घोषणा RVO_MASK        3
#घोषणा EXT_TYPE_MASK   1
#घोषणा PLL_L_MASK   0x7f
#घोषणा MVS_MASK        3
#घोषणा VST_MASK     0x7f
#घोषणा VID_MASK     0x1f
#घोषणा FID_MASK     0x1f
#घोषणा EXT_VID_MASK 0x3f
#घोषणा EXT_FID_MASK 0x3f


/*
 * Version 1.4 of the PSB table. This table is स्थिरructed by BIOS and is
 * to tell the OS's घातer management driver which VIDs and FIDs are
 * supported by this particular processor.
 * If the data in the PSB / PST is wrong, then this driver will program the
 * wrong values पूर्णांकo hardware, which is very likely to lead to a crash.
 */

#घोषणा PSB_ID_STRING      "AMDK7PNOW!"
#घोषणा PSB_ID_STRING_LEN  10

#घोषणा PSB_VERSION_1_4  0x14

काष्ठा psb_s अणु
	u8 signature[10];
	u8 tableversion;
	u8 flags1;
	u16 vstable;
	u8 flags2;
	u8 num_tables;
	u32 cpuid;
	u8 plllockसमय;
	u8 maxfid;
	u8 maxvid;
	u8 numps;
पूर्ण;

/* Pairs of fid/vid values are appended to the version 1.4 PSB table. */
काष्ठा pst_s अणु
	u8 fid;
	u8 vid;
पूर्ण;

अटल पूर्णांक core_voltage_pre_transition(काष्ठा घातernow_k8_data *data,
	u32 reqvid, u32 regfid);
अटल पूर्णांक core_voltage_post_transition(काष्ठा घातernow_k8_data *data, u32 reqvid);
अटल पूर्णांक core_frequency_transition(काष्ठा घातernow_k8_data *data, u32 reqfid);

अटल व्योम घातernow_k8_acpi_pst_values(काष्ठा घातernow_k8_data *data, अचिन्हित पूर्णांक index);

अटल पूर्णांक fill_घातernow_table_fidvid(काष्ठा घातernow_k8_data *data, काष्ठा cpufreq_frequency_table *घातernow_table);
