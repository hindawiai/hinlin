<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
  * Copyright (C) 2014 ARM Ltd.
 */
#अगर_अघोषित __ASM_CPU_H
#घोषणा __ASM_CPU_H

#समावेश <linux/cpu.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>

/*
 * Records attributes of an inभागidual CPU.
 */
काष्ठा cpuinfo_arm64 अणु
	काष्ठा cpu	cpu;
	काष्ठा kobject	kobj;
	u32		reg_ctr;
	u32		reg_cntfrq;
	u32		reg_dczid;
	u32		reg_midr;
	u32		reg_revidr;

	u64		reg_id_aa64dfr0;
	u64		reg_id_aa64dfr1;
	u64		reg_id_aa64isar0;
	u64		reg_id_aa64isar1;
	u64		reg_id_aa64mmfr0;
	u64		reg_id_aa64mmfr1;
	u64		reg_id_aa64mmfr2;
	u64		reg_id_aa64pfr0;
	u64		reg_id_aa64pfr1;
	u64		reg_id_aa64zfr0;

	u32		reg_id_dfr0;
	u32		reg_id_dfr1;
	u32		reg_id_isar0;
	u32		reg_id_isar1;
	u32		reg_id_isar2;
	u32		reg_id_isar3;
	u32		reg_id_isar4;
	u32		reg_id_isar5;
	u32		reg_id_isar6;
	u32		reg_id_mmfr0;
	u32		reg_id_mmfr1;
	u32		reg_id_mmfr2;
	u32		reg_id_mmfr3;
	u32		reg_id_mmfr4;
	u32		reg_id_mmfr5;
	u32		reg_id_pfr0;
	u32		reg_id_pfr1;
	u32		reg_id_pfr2;

	u32		reg_mvfr0;
	u32		reg_mvfr1;
	u32		reg_mvfr2;

	/* pseuकरो-ZCR क्रम recording maximum ZCR_EL1 LEN value: */
	u64		reg_zcr;
पूर्ण;

DECLARE_PER_CPU(काष्ठा cpuinfo_arm64, cpu_data);

व्योम cpuinfo_store_cpu(व्योम);
व्योम __init cpuinfo_store_boot_cpu(व्योम);

व्योम __init init_cpu_features(काष्ठा cpuinfo_arm64 *info);
व्योम update_cpu_features(पूर्णांक cpu, काष्ठा cpuinfo_arm64 *info,
				 काष्ठा cpuinfo_arm64 *boot);

#पूर्ण_अगर /* __ASM_CPU_H */
