<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#समावेश "qedi_dbg.h"
#समावेश <linux/vदो_स्मृति.h>

व्योम
qedi_dbg_err(काष्ठा qedi_dbg_ctx *qedi, स्थिर अक्षर *func, u32 line,
	     स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	अगर (likely(qedi) && likely(qedi->pdev))
		pr_err("[%s]:[%s:%d]:%d: %pV", dev_name(&qedi->pdev->dev),
		       func, line, qedi->host_no, &vaf);
	अन्यथा
		pr_err("[0000:00:00.0]:[%s:%d]: %pV", func, line, &vaf);

	बहु_पूर्ण(va);
पूर्ण

व्योम
qedi_dbg_warn(काष्ठा qedi_dbg_ctx *qedi, स्थिर अक्षर *func, u32 line,
	      स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	अगर (!(qedi_dbg_log & QEDI_LOG_WARN))
		जाओ ret;

	अगर (likely(qedi) && likely(qedi->pdev))
		pr_warn("[%s]:[%s:%d]:%d: %pV", dev_name(&qedi->pdev->dev),
			func, line, qedi->host_no, &vaf);
	अन्यथा
		pr_warn("[0000:00:00.0]:[%s:%d]: %pV", func, line, &vaf);

ret:
	बहु_पूर्ण(va);
पूर्ण

व्योम
qedi_dbg_notice(काष्ठा qedi_dbg_ctx *qedi, स्थिर अक्षर *func, u32 line,
		स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	अगर (!(qedi_dbg_log & QEDI_LOG_NOTICE))
		जाओ ret;

	अगर (likely(qedi) && likely(qedi->pdev))
		pr_notice("[%s]:[%s:%d]:%d: %pV",
			  dev_name(&qedi->pdev->dev), func, line,
			  qedi->host_no, &vaf);
	अन्यथा
		pr_notice("[0000:00:00.0]:[%s:%d]: %pV", func, line, &vaf);

ret:
	बहु_पूर्ण(va);
पूर्ण

व्योम
qedi_dbg_info(काष्ठा qedi_dbg_ctx *qedi, स्थिर अक्षर *func, u32 line,
	      u32 level, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	अगर (!(qedi_dbg_log & level))
		जाओ ret;

	अगर (likely(qedi) && likely(qedi->pdev))
		pr_info("[%s]:[%s:%d]:%d: %pV", dev_name(&qedi->pdev->dev),
			func, line, qedi->host_no, &vaf);
	अन्यथा
		pr_info("[0000:00:00.0]:[%s:%d]: %pV", func, line, &vaf);

ret:
	बहु_पूर्ण(va);
पूर्ण

पूर्णांक
qedi_create_sysfs_attr(काष्ठा Scsi_Host *shost, काष्ठा sysfs_bin_attrs *iter)
अणु
	पूर्णांक ret = 0;

	क्रम (; iter->name; iter++) अणु
		ret = sysfs_create_bin_file(&shost->shost_gendev.kobj,
					    iter->attr);
		अगर (ret)
			pr_err("Unable to create sysfs %s attr, err(%d).\n",
			       iter->name, ret);
	पूर्ण
	वापस ret;
पूर्ण

व्योम
qedi_हटाओ_sysfs_attr(काष्ठा Scsi_Host *shost, काष्ठा sysfs_bin_attrs *iter)
अणु
	क्रम (; iter->name; iter++)
		sysfs_हटाओ_bin_file(&shost->shost_gendev.kobj, iter->attr);
पूर्ण
