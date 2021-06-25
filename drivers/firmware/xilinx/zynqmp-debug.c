<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Zynq MPSoC Firmware layer क्रम debugfs APIs
 *
 *  Copyright (C) 2014-2018 Xilinx, Inc.
 *
 *  Michal Simek <michal.simek@xilinx.com>
 *  Davorin Mista <davorin.mista@aggios.com>
 *  Jolly Shah <jollys@xilinx.com>
 *  Rajan Vaja <rajanv@xilinx.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/firmware/xlnx-zynqmp.h>
#समावेश "zynqmp-debug.h"

#घोषणा PM_API_NAME_LEN			50

काष्ठा pm_api_info अणु
	u32 api_id;
	अक्षर api_name[PM_API_NAME_LEN];
	अक्षर api_name_len;
पूर्ण;

अटल अक्षर debugfs_buf[PAGE_SIZE];

#घोषणा PM_API(id)		 अणुid, #id, म_माप(#id)पूर्ण
अटल काष्ठा pm_api_info pm_api_list[] = अणु
	PM_API(PM_GET_API_VERSION),
	PM_API(PM_QUERY_DATA),
पूर्ण;

अटल काष्ठा dentry *firmware_debugfs_root;

/**
 * zynqmp_pm_argument_value() - Extract argument value from a PM-API request
 * @arg:	Entered PM-API argument in string क्रमmat
 *
 * Return: Argument value in अचिन्हित पूर्णांकeger क्रमmat on success
 *	   0 otherwise
 */
अटल u64 zynqmp_pm_argument_value(अक्षर *arg)
अणु
	u64 value;

	अगर (!arg)
		वापस 0;

	अगर (!kstrtou64(arg, 0, &value))
		वापस value;

	वापस 0;
पूर्ण

/**
 * get_pm_api_id() - Extract API-ID from a PM-API request
 * @pm_api_req:		Entered PM-API argument in string क्रमmat
 * @pm_id:		API-ID
 *
 * Return: 0 on success अन्यथा error code
 */
अटल पूर्णांक get_pm_api_id(अक्षर *pm_api_req, u32 *pm_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pm_api_list) ; i++) अणु
		अगर (!strnहालcmp(pm_api_req, pm_api_list[i].api_name,
				 pm_api_list[i].api_name_len)) अणु
			*pm_id = pm_api_list[i].api_id;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If no name was entered look क्रम PM-API ID instead */
	अगर (i == ARRAY_SIZE(pm_api_list) && kstrtouपूर्णांक(pm_api_req, 10, pm_id))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक process_api_request(u32 pm_id, u64 *pm_api_arg, u32 *pm_api_ret)
अणु
	u32 pm_api_version;
	पूर्णांक ret;
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;

	चयन (pm_id) अणु
	हाल PM_GET_API_VERSION:
		ret = zynqmp_pm_get_api_version(&pm_api_version);
		प्र_लिखो(debugfs_buf, "PM-API Version = %d.%d\n",
			pm_api_version >> 16, pm_api_version & 0xffff);
		अवरोध;
	हाल PM_QUERY_DATA:
		qdata.qid = pm_api_arg[0];
		qdata.arg1 = pm_api_arg[1];
		qdata.arg2 = pm_api_arg[2];
		qdata.arg3 = pm_api_arg[3];

		ret = zynqmp_pm_query_data(qdata, pm_api_ret);
		अगर (ret)
			अवरोध;

		चयन (qdata.qid) अणु
		हाल PM_QID_CLOCK_GET_NAME:
			प्र_लिखो(debugfs_buf, "Clock name = %s\n",
				(अक्षर *)pm_api_ret);
			अवरोध;
		हाल PM_QID_CLOCK_GET_FIXEDFACTOR_PARAMS:
			प्र_लिखो(debugfs_buf, "Multiplier = %d, Divider = %d\n",
				pm_api_ret[1], pm_api_ret[2]);
			अवरोध;
		शेष:
			प्र_लिखो(debugfs_buf,
				"data[0] = 0x%08x\ndata[1] = 0x%08x\n data[2] = 0x%08x\ndata[3] = 0x%08x\n",
				pm_api_ret[0], pm_api_ret[1],
				pm_api_ret[2], pm_api_ret[3]);
		पूर्ण
		अवरोध;
	शेष:
		प्र_लिखो(debugfs_buf, "Unsupported PM-API request\n");
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * zynqmp_pm_debugfs_api_ग_लिखो() - debugfs ग_लिखो function
 * @file:	User file
 * @ptr:	User entered PM-API string
 * @len:	Length of the userspace buffer
 * @off:	Offset within the file
 *
 * Used क्रम triggering pm api functions by writing
 * echo <pm_api_id>	> /sys/kernel/debug/zynqmp_pm/घातer or
 * echo <pm_api_name>	> /sys/kernel/debug/zynqmp_pm/घातer
 *
 * Return: Number of bytes copied अगर PM-API request succeeds,
 *	   the corresponding error code otherwise
 */
अटल sमाप_प्रकार zynqmp_pm_debugfs_api_ग_लिखो(काष्ठा file *file,
					   स्थिर अक्षर __user *ptr, माप_प्रकार len,
					   loff_t *off)
अणु
	अक्षर *kern_buff, *पंचांगp_buff;
	अक्षर *pm_api_req;
	u32 pm_id = 0;
	u64 pm_api_arg[4] = अणु0, 0, 0, 0पूर्ण;
	/* Return values from PM APIs calls */
	u32 pm_api_ret[4] = अणु0, 0, 0, 0पूर्ण;

	पूर्णांक ret;
	पूर्णांक i = 0;

	म_नकल(debugfs_buf, "");

	अगर (*off != 0 || len <= 1 || len > PAGE_SIZE - 1)
		वापस -EINVAL;

	kern_buff = memdup_user_nul(ptr, len);
	अगर (IS_ERR(kern_buff))
		वापस PTR_ERR(kern_buff);
	पंचांगp_buff = kern_buff;

	/* Read the API name from a user request */
	pm_api_req = strsep(&kern_buff, " ");

	ret = get_pm_api_id(pm_api_req, &pm_id);
	अगर (ret < 0)
		जाओ err;

	/* Read node_id and arguments from the PM-API request */
	pm_api_req = strsep(&kern_buff, " ");
	जबतक ((i < ARRAY_SIZE(pm_api_arg)) && pm_api_req) अणु
		pm_api_arg[i++] = zynqmp_pm_argument_value(pm_api_req);
		pm_api_req = strsep(&kern_buff, " ");
	पूर्ण

	ret = process_api_request(pm_id, pm_api_arg, pm_api_ret);

err:
	kमुक्त(पंचांगp_buff);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

/**
 * zynqmp_pm_debugfs_api_पढ़ो() - debugfs पढ़ो function
 * @file:	User file
 * @ptr:	Requested pm_api_version string
 * @len:	Length of the userspace buffer
 * @off:	Offset within the file
 *
 * Return: Length of the version string on success
 *	   अन्यथा error code
 */
अटल sमाप_प्रकार zynqmp_pm_debugfs_api_पढ़ो(काष्ठा file *file, अक्षर __user *ptr,
					  माप_प्रकार len, loff_t *off)
अणु
	वापस simple_पढ़ो_from_buffer(ptr, len, off, debugfs_buf,
				       म_माप(debugfs_buf));
पूर्ण

/* Setup debugfs fops */
अटल स्थिर काष्ठा file_operations fops_zynqmp_pm_dbgfs = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = zynqmp_pm_debugfs_api_ग_लिखो,
	.पढ़ो = zynqmp_pm_debugfs_api_पढ़ो,
पूर्ण;

/**
 * zynqmp_pm_api_debugfs_init - Initialize debugfs पूर्णांकerface
 *
 * Return:	None
 */
व्योम zynqmp_pm_api_debugfs_init(व्योम)
अणु
	/* Initialize debugfs पूर्णांकerface */
	firmware_debugfs_root = debugfs_create_dir("zynqmp-firmware", शून्य);
	debugfs_create_file("pm", 0660, firmware_debugfs_root, शून्य,
			    &fops_zynqmp_pm_dbgfs);
पूर्ण

/**
 * zynqmp_pm_api_debugfs_निकास - Remove debugfs पूर्णांकerface
 *
 * Return:	None
 */
व्योम zynqmp_pm_api_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(firmware_debugfs_root);
पूर्ण
