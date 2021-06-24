<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2020 Intel Corporation. All rights rsvd. */

#अगर_अघोषित _PERFMON_H_
#घोषणा _PERFMON_H_

#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/sbiपंचांगap.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/percpu-rwsem.h>
#समावेश <linux/रुको.h>
#समावेश <linux/cdev.h>
#समावेश <linux/uuid.h>
#समावेश <linux/idxd.h>
#समावेश <linux/perf_event.h>
#समावेश "registers.h"

अटल अंतरभूत काष्ठा idxd_pmu *event_to_pmu(काष्ठा perf_event *event)
अणु
	काष्ठा idxd_pmu *idxd_pmu;
	काष्ठा pmu *pmu;

	pmu = event->pmu;
	idxd_pmu = container_of(pmu, काष्ठा idxd_pmu, pmu);

	वापस idxd_pmu;
पूर्ण

अटल अंतरभूत काष्ठा idxd_device *event_to_idxd(काष्ठा perf_event *event)
अणु
	काष्ठा idxd_pmu *idxd_pmu;
	काष्ठा pmu *pmu;

	pmu = event->pmu;
	idxd_pmu = container_of(pmu, काष्ठा idxd_pmu, pmu);

	वापस idxd_pmu->idxd;
पूर्ण

अटल अंतरभूत काष्ठा idxd_device *pmu_to_idxd(काष्ठा pmu *pmu)
अणु
	काष्ठा idxd_pmu *idxd_pmu;

	idxd_pmu = container_of(pmu, काष्ठा idxd_pmu, pmu);

	वापस idxd_pmu->idxd;
पूर्ण

क्रमागत dsa_perf_events अणु
	DSA_PERF_EVENT_WQ = 0,
	DSA_PERF_EVENT_ENGINE,
	DSA_PERF_EVENT_ADDR_TRANS,
	DSA_PERF_EVENT_OP,
	DSA_PERF_EVENT_COMPL,
	DSA_PERF_EVENT_MAX,
पूर्ण;

क्रमागत filter_enc अणु
	FLT_WQ = 0,
	FLT_TC,
	FLT_PG_SZ,
	FLT_XFER_SZ,
	FLT_ENG,
	भग्न_उच्च,
पूर्ण;

#घोषणा CONFIG_RESET		0x0000000000000001
#घोषणा CNTR_RESET		0x0000000000000002
#घोषणा CNTR_ENABLE		0x0000000000000001
#घोषणा INTR_OVFL		0x0000000000000002

#घोषणा COUNTER_FREEZE		0x00000000FFFFFFFF
#घोषणा COUNTER_UNFREEZE	0x0000000000000000
#घोषणा OVERFLOW_SIZE		32

#घोषणा CNTRCFG_ENABLE		BIT(0)
#घोषणा CNTRCFG_IRQ_OVERFLOW	BIT(1)
#घोषणा CNTRCFG_CATEGORY_SHIFT	8
#घोषणा CNTRCFG_EVENT_SHIFT	32

#घोषणा PERFMON_TABLE_OFFSET(_idxd)				\
(अणु								\
	typeof(_idxd) __idxd = (_idxd);				\
	((__idxd)->reg_base + (__idxd)->perfmon_offset);	\
पूर्ण)
#घोषणा PERFMON_REG_OFFSET(idxd, offset)			\
	(PERFMON_TABLE_OFFSET(idxd) + (offset))

#घोषणा PERFCAP_REG(idxd)	(PERFMON_REG_OFFSET(idxd, IDXD_PERFCAP_OFFSET))
#घोषणा PERFRST_REG(idxd)	(PERFMON_REG_OFFSET(idxd, IDXD_PERFRST_OFFSET))
#घोषणा OVFSTATUS_REG(idxd)	(PERFMON_REG_OFFSET(idxd, IDXD_OVFSTATUS_OFFSET))
#घोषणा PERFFRZ_REG(idxd)	(PERFMON_REG_OFFSET(idxd, IDXD_PERFFRZ_OFFSET))

#घोषणा FLTCFG_REG(idxd, cntr, flt)				\
	(PERFMON_REG_OFFSET(idxd, IDXD_FLTCFG_OFFSET) +	((cntr) * 32) + ((flt) * 4))

#घोषणा CNTRCFG_REG(idxd, cntr)					\
	(PERFMON_REG_OFFSET(idxd, IDXD_CNTRCFG_OFFSET) + ((cntr) * 8))
#घोषणा CNTRDATA_REG(idxd, cntr)					\
	(PERFMON_REG_OFFSET(idxd, IDXD_CNTRDATA_OFFSET) + ((cntr) * 8))
#घोषणा CNTRCAP_REG(idxd, cntr)					\
	(PERFMON_REG_OFFSET(idxd, IDXD_CNTRCAP_OFFSET) + ((cntr) * 8))

#घोषणा EVNTCAP_REG(idxd, category) \
	(PERFMON_REG_OFFSET(idxd, IDXD_EVNTCAP_OFFSET) + ((category) * 8))

#घोषणा DEFINE_PERFMON_FORMAT_ATTR(_name, _क्रमmat)			\
अटल sमाप_प्रकार __perfmon_idxd_##_name##_show(काष्ठा kobject *kobj,	\
				काष्ठा kobj_attribute *attr,		\
				अक्षर *page)				\
अणु									\
	BUILD_BUG_ON(माप(_क्रमmat) >= PAGE_SIZE);			\
	वापस प्र_लिखो(page, _क्रमmat "\n");				\
पूर्ण									\
अटल काष्ठा kobj_attribute क्रमmat_attr_idxd_##_name =			\
	__ATTR(_name, 0444, __perfmon_idxd_##_name##_show, शून्य)

#पूर्ण_अगर
