<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम atomisp driver sysfs पूर्णांकerface
 *
 * Copyright (c) 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>

#समावेश "atomisp_compat.h"
#समावेश "atomisp_internal.h"
#समावेश "atomisp_ioctl.h"
#समावेश "atomisp_drvfs.h"
#समावेश "hmm/hmm.h"
#समावेश "ia_css_debug.h"

/*
 * _iunit_debug:
 * dbglvl: iunit css driver trace level
 * dbgopt: iunit debug option:
 *        bit 0: binary list
 *        bit 1: running binary
 *        bit 2: memory statistic
*/
काष्ठा _iunit_debug अणु
	काष्ठा device_driver	*drv;
	काष्ठा atomisp_device	*isp;
	अचिन्हित पूर्णांक		dbglvl;
	अचिन्हित पूर्णांक		dbgfun;
	अचिन्हित पूर्णांक		dbgopt;
पूर्ण;

#घोषणा OPTION_BIN_LIST			BIT(0)
#घोषणा OPTION_BIN_RUN			BIT(1)
#घोषणा OPTION_MEM_STAT			BIT(2)
#घोषणा OPTION_VALID			(OPTION_BIN_LIST \
					| OPTION_BIN_RUN \
					| OPTION_MEM_STAT)

अटल काष्ठा _iunit_debug iunit_debug = अणु
	.dbglvl = 0,
	.dbgopt = OPTION_BIN_LIST,
पूर्ण;

अटल अंतरभूत पूर्णांक iunit_dump_dbgopt(काष्ठा atomisp_device *isp,
				    अचिन्हित पूर्णांक opt)
अणु
	पूर्णांक ret = 0;

	अगर (opt & OPTION_VALID) अणु
		अगर (opt & OPTION_BIN_LIST) अणु
			ret = atomisp_css_dump_blob_inक्रम(isp);
			अगर (ret) अणु
				dev_err(isp->dev, "%s dump blob infor err[ret:%d]\n",
					__func__, ret);
				जाओ opt_err;
			पूर्ण
		पूर्ण

		अगर (opt & OPTION_BIN_RUN) अणु
			अगर (atomisp_streaming_count(isp)) अणु
				atomisp_css_dump_sp_raw_copy_linecount(true);
				atomisp_css_debug_dump_isp_binary();
			पूर्ण अन्यथा अणु
				ret = -EPERM;
				dev_err(isp->dev, "%s dump running bin err[ret:%d]\n",
					__func__, ret);
				जाओ opt_err;
			पूर्ण
		पूर्ण

		अगर (opt & OPTION_MEM_STAT)
			hmm_show_mem_stat(__func__, __LINE__);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		dev_err(isp->dev, "%s dump nothing[ret=%d]\n", __func__, ret);
	पूर्ण

opt_err:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iunit_dbglvl_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	iunit_debug.dbglvl = dbg_level;
	वापस प्र_लिखो(buf, "dtrace level:%u\n", iunit_debug.dbglvl);
पूर्ण

अटल sमाप_प्रकार iunit_dbglvl_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				  माप_प्रकार size)
अणु
	अगर (kstrtouपूर्णांक(buf, 10, &iunit_debug.dbglvl)
	    || iunit_debug.dbglvl < 1
	    || iunit_debug.dbglvl > 9) अणु
		वापस -दुस्फल;
	पूर्ण
	ia_css_debug_set_dtrace_level(iunit_debug.dbglvl);

	वापस size;
पूर्ण

अटल sमाप_प्रकार iunit_dbgfun_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	iunit_debug.dbgfun = atomisp_get_css_dbgfunc();
	वापस प्र_लिखो(buf, "dbgfun opt:%u\n", iunit_debug.dbgfun);
पूर्ण

अटल sमाप_प्रकार iunit_dbgfun_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				  माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक opt;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &opt);
	अगर (ret)
		वापस ret;

	ret = atomisp_set_css_dbgfunc(iunit_debug.isp, opt);
	अगर (ret)
		वापस ret;

	iunit_debug.dbgfun = opt;

	वापस size;
पूर्ण

अटल sमाप_प्रकार iunit_dbgopt_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "option:0x%x\n", iunit_debug.dbgopt);
पूर्ण

अटल sमाप_प्रकार iunit_dbgopt_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				  माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक opt;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &opt);
	अगर (ret)
		वापस ret;

	iunit_debug.dbgopt = opt;
	ret = iunit_dump_dbgopt(iunit_debug.isp, iunit_debug.dbgopt);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल स्थिर काष्ठा driver_attribute iunit_drvfs_attrs[] = अणु
	__ATTR(dbglvl, 0644, iunit_dbglvl_show, iunit_dbglvl_store),
	__ATTR(dbgfun, 0644, iunit_dbgfun_show, iunit_dbgfun_store),
	__ATTR(dbgopt, 0644, iunit_dbgopt_show, iunit_dbgopt_store),
पूर्ण;

अटल पूर्णांक iunit_drvfs_create_files(काष्ठा device_driver *drv)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(iunit_drvfs_attrs); i++)
		ret |= driver_create_file(drv, &iunit_drvfs_attrs[i]);

	वापस ret;
पूर्ण

अटल व्योम iunit_drvfs_हटाओ_files(काष्ठा device_driver *drv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(iunit_drvfs_attrs); i++)
		driver_हटाओ_file(drv, &iunit_drvfs_attrs[i]);
पूर्ण

पूर्णांक atomisp_drvfs_init(काष्ठा atomisp_device *isp)
अणु
	काष्ठा device_driver *drv = isp->dev->driver;
	पूर्णांक ret;

	iunit_debug.isp = isp;
	iunit_debug.drv = drv;

	ret = iunit_drvfs_create_files(iunit_debug.drv);
	अगर (ret) अणु
		dev_err(isp->dev, "drvfs_create_files error: %d\n", ret);
		iunit_drvfs_हटाओ_files(iunit_debug.drv);
	पूर्ण

	वापस ret;
पूर्ण

व्योम atomisp_drvfs_निकास(व्योम)
अणु
	iunit_drvfs_हटाओ_files(iunit_debug.drv);
पूर्ण
