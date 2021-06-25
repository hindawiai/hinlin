<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* n2rng.h: Niagara2 RNG defines.
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */

#अगर_अघोषित _N2RNG_H
#घोषणा _N2RNG_H

/* ver1 devices - n2-rng, vf-rng, kt-rng */
#घोषणा RNG_v1_CTL_WAIT       0x0000000001fffe00ULL /* Minimum रुको समय    */
#घोषणा RNG_v1_CTL_WAIT_SHIFT 9
#घोषणा RNG_v1_CTL_BYPASS     0x0000000000000100ULL /* VCO voltage source   */
#घोषणा RNG_v1_CTL_VCO        0x00000000000000c0ULL /* VCO rate control     */
#घोषणा RNG_v1_CTL_VCO_SHIFT  6
#घोषणा RNG_v1_CTL_ASEL       0x0000000000000030ULL /* Analog MUX select    */
#घोषणा RNG_v1_CTL_ASEL_SHIFT 4
#घोषणा RNG_v1_CTL_ASEL_NOOUT 2

/* these are the same in v2 as in v1 */
#घोषणा RNG_CTL_LFSR       0x0000000000000008ULL /* Use LFSR or plain shअगरt */
#घोषणा RNG_CTL_ES3        0x0000000000000004ULL /* Enable entropy source 3 */
#घोषणा RNG_CTL_ES2        0x0000000000000002ULL /* Enable entropy source 2 */
#घोषणा RNG_CTL_ES1        0x0000000000000001ULL /* Enable entropy source 1 */

/* ver2 devices - m4-rng, m7-rng */
#घोषणा RNG_v2_CTL_WAIT       0x0000000007fff800ULL /* Minimum रुको समय    */
#घोषणा RNG_v2_CTL_WAIT_SHIFT 12
#घोषणा RNG_v2_CTL_BYPASS     0x0000000000000400ULL /* VCO voltage source   */
#घोषणा RNG_v2_CTL_VCO        0x0000000000000300ULL /* VCO rate control     */
#घोषणा RNG_v2_CTL_VCO_SHIFT  9
#घोषणा RNG_v2_CTL_PERF       0x0000000000000180ULL /* Perf */
#घोषणा RNG_v2_CTL_ASEL       0x0000000000000070ULL /* Analog MUX select    */
#घोषणा RNG_v2_CTL_ASEL_SHIFT 4
#घोषणा RNG_v2_CTL_ASEL_NOOUT 7


#घोषणा HV_FAST_RNG_GET_DIAG_CTL	0x130
#घोषणा HV_FAST_RNG_CTL_READ		0x131
#घोषणा HV_FAST_RNG_CTL_WRITE		0x132
#घोषणा HV_FAST_RNG_DATA_READ_DIAG	0x133
#घोषणा HV_FAST_RNG_DATA_READ		0x134

#घोषणा HV_RNG_STATE_UNCONFIGURED	0
#घोषणा HV_RNG_STATE_CONFIGURED		1
#घोषणा HV_RNG_STATE_HEALTHCHECK	2
#घोषणा HV_RNG_STATE_ERROR		3

#घोषणा HV_RNG_NUM_CONTROL		4

#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ sun4v_rng_get_diag_ctl(व्योम);
बाह्य अचिन्हित दीर्घ sun4v_rng_ctl_पढ़ो_v1(अचिन्हित दीर्घ ctl_regs_ra,
					   अचिन्हित दीर्घ *state,
					   अचिन्हित दीर्घ *tick_delta);
बाह्य अचिन्हित दीर्घ sun4v_rng_ctl_पढ़ो_v2(अचिन्हित दीर्घ ctl_regs_ra,
					   अचिन्हित दीर्घ unit,
					   अचिन्हित दीर्घ *state,
					   अचिन्हित दीर्घ *tick_delta,
					   अचिन्हित दीर्घ *watchकरोg,
					   अचिन्हित दीर्घ *ग_लिखो_status);
बाह्य अचिन्हित दीर्घ sun4v_rng_ctl_ग_लिखो_v1(अचिन्हित दीर्घ ctl_regs_ra,
					    अचिन्हित दीर्घ state,
					    अचिन्हित दीर्घ ग_लिखो_समयout,
					    अचिन्हित दीर्घ *tick_delta);
बाह्य अचिन्हित दीर्घ sun4v_rng_ctl_ग_लिखो_v2(अचिन्हित दीर्घ ctl_regs_ra,
					    अचिन्हित दीर्घ state,
					    अचिन्हित दीर्घ ग_लिखो_समयout,
					    अचिन्हित दीर्घ unit);
बाह्य अचिन्हित दीर्घ sun4v_rng_data_पढ़ो_diag_v1(अचिन्हित दीर्घ data_ra,
						 अचिन्हित दीर्घ len,
						 अचिन्हित दीर्घ *tick_delta);
बाह्य अचिन्हित दीर्घ sun4v_rng_data_पढ़ो_diag_v2(अचिन्हित दीर्घ data_ra,
						 अचिन्हित दीर्घ len,
						 अचिन्हित दीर्घ unit,
						 अचिन्हित दीर्घ *tick_delta);
बाह्य अचिन्हित दीर्घ sun4v_rng_data_पढ़ो(अचिन्हित दीर्घ data_ra,
					 अचिन्हित दीर्घ *tick_delta);

क्रमागत n2rng_compat_id अणु
	N2_n2_rng,
	N2_vf_rng,
	N2_kt_rng,
	N2_m4_rng,
	N2_m7_rng,
पूर्ण;

काष्ठा n2rng_ढाँचा अणु
	क्रमागत n2rng_compat_id id;
	पूर्णांक multi_capable;
	पूर्णांक chip_version;
पूर्ण;

काष्ठा n2rng_unit अणु
	u64			control[HV_RNG_NUM_CONTROL];
पूर्ण;

काष्ठा n2rng अणु
	काष्ठा platक्रमm_device	*op;

	अचिन्हित दीर्घ		flags;
#घोषणा N2RNG_FLAG_MULTI	0x00000001 /* Multi-unit capable RNG */
#घोषणा N2RNG_FLAG_CONTROL	0x00000002 /* Operating in control करोमुख्य */
#घोषणा N2RNG_FLAG_READY	0x00000008 /* Ready क्रम hw-rng layer      */
#घोषणा N2RNG_FLAG_SHUTDOWN	0x00000010 /* Driver unरेजिस्टरing        */
#घोषणा N2RNG_FLAG_BUFFER_VALID	0x00000020 /* u32 buffer holds valid data */

	काष्ठा n2rng_ढाँचा	*data;
	पूर्णांक			num_units;
	काष्ठा n2rng_unit	*units;

	काष्ठा hwrng		hwrng;
	u32			buffer;

	/* Registered hypervisor group API major and minor version.  */
	अचिन्हित दीर्घ		hvapi_major;
	अचिन्हित दीर्घ		hvapi_minor;

	काष्ठा delayed_work	work;

	अचिन्हित दीर्घ		hv_state; /* HV_RNG_STATE_foo */

	अचिन्हित दीर्घ		health_check_sec;
	अचिन्हित दीर्घ		accum_cycles;
	अचिन्हित दीर्घ		wd_समयo;
#घोषणा N2RNG_HEALTH_CHECK_SEC_DEFAULT	0
#घोषणा N2RNG_ACCUM_CYCLES_DEFAULT	2048
#घोषणा N2RNG_WD_TIMEO_DEFAULT		0

	u64			scratch_control[HV_RNG_NUM_CONTROL];

#घोषणा RNG_v1_SELFTEST_TICKS	38859
#घोषणा RNG_v1_SELFTEST_VAL	((u64)0xB8820C7BD387E32C)
#घोषणा RNG_v2_SELFTEST_TICKS	64
#घोषणा RNG_v2_SELFTEST_VAL	((u64)0xffffffffffffffff)
#घोषणा SELFTEST_POLY		((u64)0x231DCEE91262B8A3)
#घोषणा SELFTEST_MATCH_GOAL	6
#घोषणा SELFTEST_LOOPS_MAX	40000
#घोषणा SELFTEST_BUFFER_WORDS	8

	u64			test_data;
	u64			test_control[HV_RNG_NUM_CONTROL];
	u64			test_buffer[SELFTEST_BUFFER_WORDS];
पूर्ण;

#घोषणा N2RNG_BLOCK_LIMIT	60000
#घोषणा N2RNG_BUSY_LIMIT	100
#घोषणा N2RNG_HCHECK_LIMIT	100

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* _N2RNG_H */
