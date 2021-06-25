<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2017 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_MIPS_CPS_H__
#घोषणा __MIPS_ASM_MIPS_CPS_H__

#समावेश <linux/पन.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/mips-boards/launch.h>

बाह्य अचिन्हित दीर्घ __cps_access_bad_size(व्योम)
	__compileसमय_error("Bad size for CPS accessor");

#घोषणा CPS_ACCESSOR_A(unit, off, name)					\
अटल अंतरभूत व्योम *addr_##unit##_##name(व्योम)				\
अणु									\
	वापस mips_##unit##_base + (off);				\
पूर्ण

#घोषणा CPS_ACCESSOR_R(unit, sz, name)					\
अटल अंतरभूत uपूर्णांक##sz##_t पढ़ो_##unit##_##name(व्योम)			\
अणु									\
	uपूर्णांक64_t val64;							\
									\
	चयन (sz) अणु							\
	हाल 32:							\
		वापस __raw_पढ़ोl(addr_##unit##_##name());		\
									\
	हाल 64:							\
		अगर (mips_cm_is64)					\
			वापस __raw_पढ़ोq(addr_##unit##_##name());	\
									\
		val64 = __raw_पढ़ोl(addr_##unit##_##name() + 4);	\
		val64 <<= 32;						\
		val64 |= __raw_पढ़ोl(addr_##unit##_##name());		\
		वापस val64;						\
									\
	शेष:							\
		वापस __cps_access_bad_size();				\
	पूर्ण								\
पूर्ण

#घोषणा CPS_ACCESSOR_W(unit, sz, name)					\
अटल अंतरभूत व्योम ग_लिखो_##unit##_##name(uपूर्णांक##sz##_t val)		\
अणु									\
	चयन (sz) अणु							\
	हाल 32:							\
		__raw_ग_लिखोl(val, addr_##unit##_##name());		\
		अवरोध;							\
									\
	हाल 64:							\
		अगर (mips_cm_is64) अणु					\
			__raw_ग_लिखोq(val, addr_##unit##_##name());	\
			अवरोध;						\
		पूर्ण							\
									\
		__raw_ग_लिखोl((uपूर्णांक64_t)val >> 32,			\
			     addr_##unit##_##name() + 4);		\
		__raw_ग_लिखोl(val, addr_##unit##_##name());		\
		अवरोध;							\
									\
	शेष:							\
		__cps_access_bad_size();				\
		अवरोध;							\
	पूर्ण								\
पूर्ण

#घोषणा CPS_ACCESSOR_M(unit, sz, name)					\
अटल अंतरभूत व्योम change_##unit##_##name(uपूर्णांक##sz##_t mask,		\
					  uपूर्णांक##sz##_t val)		\
अणु									\
	uपूर्णांक##sz##_t reg_val = पढ़ो_##unit##_##name();			\
	reg_val &= ~mask;						\
	reg_val |= val;							\
	ग_लिखो_##unit##_##name(reg_val);					\
पूर्ण									\
									\
अटल अंतरभूत व्योम set_##unit##_##name(uपूर्णांक##sz##_t val)		\
अणु									\
	change_##unit##_##name(val, val);				\
पूर्ण									\
									\
अटल अंतरभूत व्योम clear_##unit##_##name(uपूर्णांक##sz##_t val)		\
अणु									\
	change_##unit##_##name(val, 0);					\
पूर्ण

#घोषणा CPS_ACCESSOR_RO(unit, sz, off, name)				\
	CPS_ACCESSOR_A(unit, off, name)					\
	CPS_ACCESSOR_R(unit, sz, name)

#घोषणा CPS_ACCESSOR_WO(unit, sz, off, name)				\
	CPS_ACCESSOR_A(unit, off, name)					\
	CPS_ACCESSOR_W(unit, sz, name)

#घोषणा CPS_ACCESSOR_RW(unit, sz, off, name)				\
	CPS_ACCESSOR_A(unit, off, name)					\
	CPS_ACCESSOR_R(unit, sz, name)					\
	CPS_ACCESSOR_W(unit, sz, name)					\
	CPS_ACCESSOR_M(unit, sz, name)

#समावेश <यंत्र/mips-cm.h>
#समावेश <यंत्र/mips-cpc.h>
#समावेश <यंत्र/mips-gic.h>

/**
 * mips_cps_numclusters - वापस the number of clusters present in the प्रणाली
 *
 * Returns the number of clusters in the प्रणाली.
 */
अटल अंतरभूत अचिन्हित पूर्णांक mips_cps_numclusters(व्योम)
अणु
	अचिन्हित पूर्णांक num_clusters;

	अगर (mips_cm_revision() < CM_REV_CM3_5)
		वापस 1;

	num_clusters = पढ़ो_gcr_config() & CM_GCR_CONFIG_NUM_CLUSTERS;
	num_clusters >>= __ffs(CM_GCR_CONFIG_NUM_CLUSTERS);
	वापस num_clusters;
पूर्ण

/**
 * mips_cps_cluster_config - वापस (GCR|CPC)_CONFIG from a cluster
 * @cluster: the ID of the cluster whose config we want
 *
 * Read the value of GCR_CONFIG (or its CPC_CONFIG mirror) from a @cluster.
 *
 * Returns the value of GCR_CONFIG.
 */
अटल अंतरभूत uपूर्णांक64_t mips_cps_cluster_config(अचिन्हित पूर्णांक cluster)
अणु
	uपूर्णांक64_t config;

	अगर (mips_cm_revision() < CM_REV_CM3_5) अणु
		/*
		 * Prior to CM 3.5 we करोn't have the notion of multiple
		 * clusters so we can trivially पढ़ो the GCR_CONFIG रेजिस्टर
		 * within this cluster.
		 */
		WARN_ON(cluster != 0);
		config = पढ़ो_gcr_config();
	पूर्ण अन्यथा अणु
		/*
		 * From CM 3.5 onwards we पढ़ो the CPC_CONFIG mirror of
		 * GCR_CONFIG via the redirect region, since the CPC is always
		 * घातered up allowing us not to need to घातer up the CM.
		 */
		mips_cm_lock_other(cluster, 0, 0, CM_GCR_Cx_OTHER_BLOCK_GLOBAL);
		config = पढ़ो_cpc_redir_config();
		mips_cm_unlock_other();
	पूर्ण

	वापस config;
पूर्ण

/**
 * mips_cps_numcores - वापस the number of cores present in a cluster
 * @cluster: the ID of the cluster whose core count we want
 *
 * Returns the value of the PCORES field of the GCR_CONFIG रेजिस्टर plus 1, or
 * zero अगर no Coherence Manager is present.
 */
अटल अंतरभूत अचिन्हित पूर्णांक mips_cps_numcores(अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक ncores;

	अगर (!mips_cm_present())
		वापस 0;

	/* Add one beक्रमe masking to handle 0xff indicating no cores */
	ncores = (mips_cps_cluster_config(cluster) + 1) & CM_GCR_CONFIG_PCORES;

	अगर (IS_ENABLED(CONFIG_SOC_MT7621)) अणु
		काष्ठा cpulaunch *launch;

		/*
		 * Ralink MT7621S SoC is single core, but the GCR_CONFIG method
		 * always reports 2 cores. Check the second core's LAUNCH_FREADY
		 * flag to detect अगर the second core is missing. This method
		 * only works beक्रमe the core has been started.
		 */
		launch = (काष्ठा cpulaunch *)CKSEG0ADDR(CPULAUNCH);
		launch += 2; /* MT7621 has 2 VPEs per core */
		अगर (!(launch->flags & LAUNCH_FREADY))
			ncores = 1;
	पूर्ण

	वापस ncores;
पूर्ण

/**
 * mips_cps_numiocu - वापस the number of IOCUs present in a cluster
 * @cluster: the ID of the cluster whose IOCU count we want
 *
 * Returns the value of the NUMIOCU field of the GCR_CONFIG रेजिस्टर, or zero
 * अगर no Coherence Manager is present.
 */
अटल अंतरभूत अचिन्हित पूर्णांक mips_cps_numiocu(अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक num_iocu;

	अगर (!mips_cm_present())
		वापस 0;

	num_iocu = mips_cps_cluster_config(cluster) & CM_GCR_CONFIG_NUMIOCU;
	num_iocu >>= __ffs(CM_GCR_CONFIG_NUMIOCU);
	वापस num_iocu;
पूर्ण

/**
 * mips_cps_numvps - वापस the number of VPs (thपढ़ोs) supported by a core
 * @cluster: the ID of the cluster containing the core we want to examine
 * @core: the ID of the core whose VP count we want
 *
 * Returns the number of Virtual Processors (VPs, ie. hardware thपढ़ोs) that
 * are supported by the given @core in the given @cluster. If the core or the
 * kernel करो not support hardware mutlti-thपढ़ोing this वापसs 1.
 */
अटल अंतरभूत अचिन्हित पूर्णांक mips_cps_numvps(अचिन्हित पूर्णांक cluster, अचिन्हित पूर्णांक core)
अणु
	अचिन्हित पूर्णांक cfg;

	अगर (!mips_cm_present())
		वापस 1;

	अगर ((!IS_ENABLED(CONFIG_MIPS_MT_SMP) || !cpu_has_mipsmt)
		&& (!IS_ENABLED(CONFIG_CPU_MIPSR6) || !cpu_has_vp))
		वापस 1;

	mips_cm_lock_other(cluster, core, 0, CM_GCR_Cx_OTHER_BLOCK_LOCAL);

	अगर (mips_cm_revision() < CM_REV_CM3_5) अणु
		/*
		 * Prior to CM 3.5 we can only have one cluster & करोn't have
		 * CPC_Cx_CONFIG, so we पढ़ो GCR_Cx_CONFIG.
		 */
		cfg = पढ़ो_gcr_co_config();
	पूर्ण अन्यथा अणु
		/*
		 * From CM 3.5 onwards we पढ़ो CPC_Cx_CONFIG because the CPC is
		 * always घातered, which allows us to not worry about घातering
		 * up the cluster's CM here.
		 */
		cfg = पढ़ो_cpc_co_config();
	पूर्ण

	mips_cm_unlock_other();

	वापस (cfg + 1) & CM_GCR_Cx_CONFIG_PVPE;
पूर्ण

#पूर्ण_अगर /* __MIPS_ASM_MIPS_CPS_H__ */
