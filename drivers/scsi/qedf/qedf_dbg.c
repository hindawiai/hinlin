<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 Cavium Inc.
 */
#समावेश "qedf_dbg.h"
#समावेश <linux/vदो_स्मृति.h>

व्योम
qedf_dbg_err(काष्ठा qedf_dbg_ctx *qedf, स्थिर अक्षर *func, u32 line,
	      स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	अगर (likely(qedf) && likely(qedf->pdev))
		pr_err("[%s]:[%s:%d]:%d: %pV", dev_name(&(qedf->pdev->dev)),
			func, line, qedf->host_no, &vaf);
	अन्यथा
		pr_err("[0000:00:00.0]:[%s:%d]: %pV", func, line, &vaf);

	बहु_पूर्ण(va);
पूर्ण

व्योम
qedf_dbg_warn(काष्ठा qedf_dbg_ctx *qedf, स्थिर अक्षर *func, u32 line,
	       स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	अगर (!(qedf_debug & QEDF_LOG_WARN))
		जाओ ret;

	अगर (likely(qedf) && likely(qedf->pdev))
		pr_warn("[%s]:[%s:%d]:%d: %pV", dev_name(&(qedf->pdev->dev)),
			func, line, qedf->host_no, &vaf);
	अन्यथा
		pr_warn("[0000:00:00.0]:[%s:%d]: %pV", func, line, &vaf);

ret:
	बहु_पूर्ण(va);
पूर्ण

व्योम
qedf_dbg_notice(काष्ठा qedf_dbg_ctx *qedf, स्थिर अक्षर *func, u32 line,
		 स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	अगर (!(qedf_debug & QEDF_LOG_NOTICE))
		जाओ ret;

	अगर (likely(qedf) && likely(qedf->pdev))
		pr_notice("[%s]:[%s:%d]:%d: %pV",
			  dev_name(&(qedf->pdev->dev)), func, line,
			  qedf->host_no, &vaf);
	अन्यथा
		pr_notice("[0000:00:00.0]:[%s:%d]: %pV", func, line, &vaf);

ret:
	बहु_पूर्ण(va);
पूर्ण

व्योम
qedf_dbg_info(काष्ठा qedf_dbg_ctx *qedf, स्थिर अक्षर *func, u32 line,
	       u32 level, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	अगर (!(qedf_debug & level))
		जाओ ret;

	अगर (likely(qedf) && likely(qedf->pdev))
		pr_info("[%s]:[%s:%d]:%d: %pV", dev_name(&(qedf->pdev->dev)),
			func, line, qedf->host_no, &vaf);
	अन्यथा
		pr_info("[0000:00:00.0]:[%s:%d]: %pV", func, line, &vaf);

ret:
	बहु_पूर्ण(va);
पूर्ण

पूर्णांक
qedf_alloc_grc_dump_buf(u8 **buf, uपूर्णांक32_t len)
अणु
		*buf = vदो_स्मृति(len);
		अगर (!(*buf))
			वापस -ENOMEM;

		स_रखो(*buf, 0, len);
		वापस 0;
पूर्ण

व्योम
qedf_मुक्त_grc_dump_buf(uपूर्णांक8_t **buf)
अणु
		vमुक्त(*buf);
		*buf = शून्य;
पूर्ण

पूर्णांक
qedf_get_grc_dump(काष्ठा qed_dev *cdev, स्थिर काष्ठा qed_common_ops *common,
		   u8 **buf, uपूर्णांक32_t *grcsize)
अणु
	अगर (!*buf)
		वापस -EINVAL;

	वापस common->dbg_all_data(cdev, *buf);
पूर्ण

व्योम
qedf_uevent_emit(काष्ठा Scsi_Host *shost, u32 code, अक्षर *msg)
अणु
	अक्षर event_string[40];
	अक्षर *envp[] = अणुevent_string, शून्यपूर्ण;

	स_रखो(event_string, 0, माप(event_string));
	चयन (code) अणु
	हाल QEDF_UEVENT_CODE_GRCDUMP:
		अगर (msg)
			strscpy(event_string, msg, माप(event_string));
		अन्यथा
			प्र_लिखो(event_string, "GRCDUMP=%u", shost->host_no);
		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	kobject_uevent_env(&shost->shost_gendev.kobj, KOBJ_CHANGE, envp);
पूर्ण

पूर्णांक
qedf_create_sysfs_attr(काष्ठा Scsi_Host *shost, काष्ठा sysfs_bin_attrs *iter)
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
qedf_हटाओ_sysfs_attr(काष्ठा Scsi_Host *shost, काष्ठा sysfs_bin_attrs *iter)
अणु
	क्रम (; iter->name; iter++)
		sysfs_हटाओ_bin_file(&shost->shost_gendev.kobj, iter->attr);
पूर्ण
