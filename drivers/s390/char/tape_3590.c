<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    tape device discipline क्रम 3590 tapes.
 *
 *    Copyright IBM Corp. 2001, 2009
 *    Author(s): Stefan Bader <shbader@de.ibm.com>
 *		 Michael Holzheu <holzheu@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "tape_3590"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/bपन.स>
#समावेश <यंत्र/ebcdic.h>

#घोषणा TAPE_DBF_AREA	tape_3590_dbf
#घोषणा बफ_मानE 512	/* size of buffers क्रम dynamic generated messages */

#समावेश "tape.h"
#समावेश "tape_std.h"
#समावेश "tape_3590.h"

अटल काष्ठा workqueue_काष्ठा *tape_3590_wq;

/*
 * Poपूर्णांकer to debug area.
 */
debug_info_t *TAPE_DBF_AREA = शून्य;
EXPORT_SYMBOL(TAPE_DBF_AREA);

/*******************************************************************
 * Error Recovery functions:
 * - Read Opposite:		 implemented
 * - Read Device (buffered) log: BRA
 * - Read Library log:		 BRA
 * - Swap Devices:		 BRA
 * - Long Busy:			 implemented
 * - Special Intercept:		 BRA
 * - Read Alternate:		 implemented
 *******************************************************************/

अटल स्थिर अक्षर *tape_3590_msg[TAPE_3590_MAX_MSG] = अणु
	[0x00] = "",
	[0x10] = "Lost Sense",
	[0x11] = "Assigned Elsewhere",
	[0x12] = "Allegiance Reset",
	[0x13] = "Shared Access Violation",
	[0x20] = "Command Reject",
	[0x21] = "Configuration Error",
	[0x22] = "Protection Exception",
	[0x23] = "Write Protect",
	[0x24] = "Write Length",
	[0x25] = "Read-Only Format",
	[0x31] = "Beginning of Partition",
	[0x33] = "End of Partition",
	[0x34] = "End of Data",
	[0x35] = "Block not found",
	[0x40] = "Device Intervention",
	[0x41] = "Loader Intervention",
	[0x42] = "Library Intervention",
	[0x50] = "Write Error",
	[0x51] = "Erase Error",
	[0x52] = "Formatting Error",
	[0x53] = "Read Error",
	[0x54] = "Unsupported Format",
	[0x55] = "No Formatting",
	[0x56] = "Positioning lost",
	[0x57] = "Read Length",
	[0x60] = "Unsupported Medium",
	[0x61] = "Medium Length Error",
	[0x62] = "Medium removed",
	[0x64] = "Load Check",
	[0x65] = "Unload Check",
	[0x70] = "Equipment Check",
	[0x71] = "Bus out Check",
	[0x72] = "Protocol Error",
	[0x73] = "Interface Error",
	[0x74] = "Overrun",
	[0x75] = "Halt Signal",
	[0x90] = "Device fenced",
	[0x91] = "Device Path fenced",
	[0xa0] = "Volume misplaced",
	[0xa1] = "Volume inaccessible",
	[0xa2] = "Volume in input",
	[0xa3] = "Volume ejected",
	[0xa4] = "All categories reserved",
	[0xa5] = "Duplicate Volume",
	[0xa6] = "Library Manager Offline",
	[0xa7] = "Library Output Station full",
	[0xa8] = "Vision System non-operational",
	[0xa9] = "Library Manager Equipment Check",
	[0xaa] = "Library Equipment Check",
	[0xab] = "All Library Cells full",
	[0xac] = "No Cleaner Volumes in Library",
	[0xad] = "I/O Station door open",
	[0xae] = "Subsystem environmental alert",
पूर्ण;

अटल पूर्णांक crypt_supported(काष्ठा tape_device *device)
अणु
	वापस TAPE390_CRYPT_SUPPORTED(TAPE_3590_CRYPT_INFO(device));
पूर्ण

अटल पूर्णांक crypt_enabled(काष्ठा tape_device *device)
अणु
	वापस TAPE390_CRYPT_ON(TAPE_3590_CRYPT_INFO(device));
पूर्ण

अटल व्योम ext_to_पूर्णांक_kekl(काष्ठा tape390_kekl *in,
			    काष्ठा tape3592_kekl *out)
अणु
	पूर्णांक len;

	स_रखो(out, 0, माप(*out));
	अगर (in->type == TAPE390_KEKL_TYPE_HASH)
		out->flags |= 0x40;
	अगर (in->type_on_tape == TAPE390_KEKL_TYPE_HASH)
		out->flags |= 0x80;
	len = min(माप(out->label), म_माप(in->label));
	स_नकल(out->label, in->label, len);
	स_रखो(out->label + len, ' ', माप(out->label) - len);
	ASCEBC(out->label, माप(out->label));
पूर्ण

अटल व्योम पूर्णांक_to_ext_kekl(काष्ठा tape3592_kekl *in,
			    काष्ठा tape390_kekl *out)
अणु
	स_रखो(out, 0, माप(*out));
	अगर(in->flags & 0x40)
		out->type = TAPE390_KEKL_TYPE_HASH;
	अन्यथा
		out->type = TAPE390_KEKL_TYPE_LABEL;
	अगर(in->flags & 0x80)
		out->type_on_tape = TAPE390_KEKL_TYPE_HASH;
	अन्यथा
		out->type_on_tape = TAPE390_KEKL_TYPE_LABEL;
	स_नकल(out->label, in->label, माप(in->label));
	EBCASC(out->label, माप(in->label));
	strim(out->label);
पूर्ण

अटल व्योम पूर्णांक_to_ext_kekl_pair(काष्ठा tape3592_kekl_pair *in,
				 काष्ठा tape390_kekl_pair *out)
अणु
	अगर (in->count == 0) अणु
		out->kekl[0].type = TAPE390_KEKL_TYPE_NONE;
		out->kekl[0].type_on_tape = TAPE390_KEKL_TYPE_NONE;
		out->kekl[1].type = TAPE390_KEKL_TYPE_NONE;
		out->kekl[1].type_on_tape = TAPE390_KEKL_TYPE_NONE;
	पूर्ण अन्यथा अगर (in->count == 1) अणु
		पूर्णांक_to_ext_kekl(&in->kekl[0], &out->kekl[0]);
		out->kekl[1].type = TAPE390_KEKL_TYPE_NONE;
		out->kekl[1].type_on_tape = TAPE390_KEKL_TYPE_NONE;
	पूर्ण अन्यथा अगर (in->count == 2) अणु
		पूर्णांक_to_ext_kekl(&in->kekl[0], &out->kekl[0]);
		पूर्णांक_to_ext_kekl(&in->kekl[1], &out->kekl[1]);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("Invalid KEKL number: %d\n", in->count);
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक check_ext_kekl(काष्ठा tape390_kekl *kekl)
अणु
	अगर (kekl->type == TAPE390_KEKL_TYPE_NONE)
		जाओ invalid;
	अगर (kekl->type > TAPE390_KEKL_TYPE_HASH)
		जाओ invalid;
	अगर (kekl->type_on_tape == TAPE390_KEKL_TYPE_NONE)
		जाओ invalid;
	अगर (kekl->type_on_tape > TAPE390_KEKL_TYPE_HASH)
		जाओ invalid;
	अगर ((kekl->type == TAPE390_KEKL_TYPE_HASH) &&
	    (kekl->type_on_tape == TAPE390_KEKL_TYPE_LABEL))
		जाओ invalid;

	वापस 0;
invalid:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक check_ext_kekl_pair(काष्ठा tape390_kekl_pair *kekls)
अणु
	अगर (check_ext_kekl(&kekls->kekl[0]))
		जाओ invalid;
	अगर (check_ext_kekl(&kekls->kekl[1]))
		जाओ invalid;

	वापस 0;
invalid:
	वापस -EINVAL;
पूर्ण

/*
 * Query KEKLs
 */
अटल पूर्णांक tape_3592_kekl_query(काष्ठा tape_device *device,
				काष्ठा tape390_kekl_pair *ext_kekls)
अणु
	काष्ठा tape_request *request;
	काष्ठा tape3592_kekl_query_order *order;
	काष्ठा tape3592_kekl_query_data *पूर्णांक_kekls;
	पूर्णांक rc;

	DBF_EVENT(6, "tape3592_kekl_query\n");
	पूर्णांक_kekls = kदो_स्मृति(माप(*पूर्णांक_kekls), GFP_KERNEL|GFP_DMA);
	अगर (!पूर्णांक_kekls)
		वापस -ENOMEM;
	request = tape_alloc_request(2, माप(*order));
	अगर (IS_ERR(request)) अणु
		rc = PTR_ERR(request);
		जाओ fail_दो_स्मृति;
	पूर्ण
	order = request->cpdata;
	स_रखो(order,0,माप(*order));
	order->code = 0xe2;
	order->max_count = 2;
	request->op = TO_KEKL_QUERY;
	tape_ccw_cc(request->cpaddr, PERF_SUBSYS_FUNC, माप(*order), order);
	tape_ccw_end(request->cpaddr + 1, READ_SS_DATA, माप(*पूर्णांक_kekls),
		     पूर्णांक_kekls);
	rc = tape_करो_io(device, request);
	अगर (rc)
		जाओ fail_request;
	पूर्णांक_to_ext_kekl_pair(&पूर्णांक_kekls->kekls, ext_kekls);

	rc = 0;
fail_request:
	tape_मुक्त_request(request);
fail_दो_स्मृति:
	kमुक्त(पूर्णांक_kekls);
	वापस rc;
पूर्ण

/*
 * IOCTL: Query KEKLs
 */
अटल पूर्णांक tape_3592_ioctl_kekl_query(काष्ठा tape_device *device,
				      अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	काष्ठा tape390_kekl_pair *ext_kekls;

	DBF_EVENT(6, "tape_3592_ioctl_kekl_query\n");
	अगर (!crypt_supported(device))
		वापस -ENOSYS;
	अगर (!crypt_enabled(device))
		वापस -EUNATCH;
	ext_kekls = kदो_स्मृति(माप(*ext_kekls), GFP_KERNEL);
	अगर (!ext_kekls)
		वापस -ENOMEM;
	rc = tape_3592_kekl_query(device, ext_kekls);
	अगर (rc != 0)
		जाओ fail;
	अगर (copy_to_user((अक्षर __user *) arg, ext_kekls, माप(*ext_kekls))) अणु
		rc = -EFAULT;
		जाओ fail;
	पूर्ण
	rc = 0;
fail:
	kमुक्त(ext_kekls);
	वापस rc;
पूर्ण

अटल पूर्णांक tape_3590_mttell(काष्ठा tape_device *device, पूर्णांक mt_count);

/*
 * Set KEKLs
 */
अटल पूर्णांक tape_3592_kekl_set(काष्ठा tape_device *device,
			      काष्ठा tape390_kekl_pair *ext_kekls)
अणु
	काष्ठा tape_request *request;
	काष्ठा tape3592_kekl_set_order *order;

	DBF_EVENT(6, "tape3592_kekl_set\n");
	अगर (check_ext_kekl_pair(ext_kekls)) अणु
		DBF_EVENT(6, "invalid kekls\n");
		वापस -EINVAL;
	पूर्ण
	अगर (tape_3590_mttell(device, 0) != 0)
		वापस -EBADSLT;
	request = tape_alloc_request(1, माप(*order));
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	order = request->cpdata;
	स_रखो(order, 0, माप(*order));
	order->code = 0xe3;
	order->kekls.count = 2;
	ext_to_पूर्णांक_kekl(&ext_kekls->kekl[0], &order->kekls.kekl[0]);
	ext_to_पूर्णांक_kekl(&ext_kekls->kekl[1], &order->kekls.kekl[1]);
	request->op = TO_KEKL_SET;
	tape_ccw_end(request->cpaddr, PERF_SUBSYS_FUNC, माप(*order), order);

	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * IOCTL: Set KEKLs
 */
अटल पूर्णांक tape_3592_ioctl_kekl_set(काष्ठा tape_device *device,
				    अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	काष्ठा tape390_kekl_pair *ext_kekls;

	DBF_EVENT(6, "tape_3592_ioctl_kekl_set\n");
	अगर (!crypt_supported(device))
		वापस -ENOSYS;
	अगर (!crypt_enabled(device))
		वापस -EUNATCH;
	ext_kekls = memdup_user((अक्षर __user *)arg, माप(*ext_kekls));
	अगर (IS_ERR(ext_kekls))
		वापस PTR_ERR(ext_kekls);
	rc = tape_3592_kekl_set(device, ext_kekls);
	kमुक्त(ext_kekls);
	वापस rc;
पूर्ण

/*
 * Enable encryption
 */
अटल काष्ठा tape_request *__tape_3592_enable_crypt(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;
	अक्षर *data;

	DBF_EVENT(6, "tape_3592_enable_crypt\n");
	अगर (!crypt_supported(device))
		वापस ERR_PTR(-ENOSYS);
	request = tape_alloc_request(2, 72);
	अगर (IS_ERR(request))
		वापस request;
	data = request->cpdata;
	स_रखो(data,0,72);

	data[0]       = 0x05;
	data[36 + 0]  = 0x03;
	data[36 + 1]  = 0x03;
	data[36 + 4]  = 0x40;
	data[36 + 6]  = 0x01;
	data[36 + 14] = 0x2f;
	data[36 + 18] = 0xc3;
	data[36 + 35] = 0x72;
	request->op = TO_CRYPT_ON;
	tape_ccw_cc(request->cpaddr, MODE_SET_CB, 36, data);
	tape_ccw_end(request->cpaddr + 1, MODE_SET_CB, 36, data + 36);
	वापस request;
पूर्ण

अटल पूर्णांक tape_3592_enable_crypt(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;

	request = __tape_3592_enable_crypt(device);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

अटल व्योम tape_3592_enable_crypt_async(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;

	request = __tape_3592_enable_crypt(device);
	अगर (!IS_ERR(request))
		tape_करो_io_async_मुक्त(device, request);
पूर्ण

/*
 * Disable encryption
 */
अटल काष्ठा tape_request *__tape_3592_disable_crypt(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;
	अक्षर *data;

	DBF_EVENT(6, "tape_3592_disable_crypt\n");
	अगर (!crypt_supported(device))
		वापस ERR_PTR(-ENOSYS);
	request = tape_alloc_request(2, 72);
	अगर (IS_ERR(request))
		वापस request;
	data = request->cpdata;
	स_रखो(data,0,72);

	data[0]       = 0x05;
	data[36 + 0]  = 0x03;
	data[36 + 1]  = 0x03;
	data[36 + 35] = 0x32;

	request->op = TO_CRYPT_OFF;
	tape_ccw_cc(request->cpaddr, MODE_SET_CB, 36, data);
	tape_ccw_end(request->cpaddr + 1, MODE_SET_CB, 36, data + 36);

	वापस request;
पूर्ण

अटल पूर्णांक tape_3592_disable_crypt(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;

	request = __tape_3592_disable_crypt(device);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

अटल व्योम tape_3592_disable_crypt_async(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;

	request = __tape_3592_disable_crypt(device);
	अगर (!IS_ERR(request))
		tape_करो_io_async_मुक्त(device, request);
पूर्ण

/*
 * IOCTL: Set encryption status
 */
अटल पूर्णांक tape_3592_ioctl_crypt_set(काष्ठा tape_device *device,
				     अचिन्हित दीर्घ arg)
अणु
	काष्ठा tape390_crypt_info info;

	DBF_EVENT(6, "tape_3592_ioctl_crypt_set\n");
	अगर (!crypt_supported(device))
		वापस -ENOSYS;
	अगर (copy_from_user(&info, (अक्षर __user *)arg, माप(info)))
		वापस -EFAULT;
	अगर (info.status & ~TAPE390_CRYPT_ON_MASK)
		वापस -EINVAL;
	अगर (info.status & TAPE390_CRYPT_ON_MASK)
		वापस tape_3592_enable_crypt(device);
	अन्यथा
		वापस tape_3592_disable_crypt(device);
पूर्ण

अटल पूर्णांक tape_3590_sense_medium(काष्ठा tape_device *device);

/*
 * IOCTL: Query enryption status
 */
अटल पूर्णांक tape_3592_ioctl_crypt_query(काष्ठा tape_device *device,
				       अचिन्हित दीर्घ arg)
अणु
	DBF_EVENT(6, "tape_3592_ioctl_crypt_query\n");
	अगर (!crypt_supported(device))
		वापस -ENOSYS;
	tape_3590_sense_medium(device);
	अगर (copy_to_user((अक्षर __user *) arg, &TAPE_3590_CRYPT_INFO(device),
		माप(TAPE_3590_CRYPT_INFO(device))))
		वापस -EFAULT;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * 3590 IOCTL Overload
 */
अटल पूर्णांक
tape_3590_ioctl(काष्ठा tape_device *device, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल TAPE390_DISPLAY: अणु
		काष्ठा display_काष्ठा disp;

		अगर (copy_from_user(&disp, (अक्षर __user *) arg, माप(disp)))
			वापस -EFAULT;

		वापस tape_std_display(device, &disp);
	पूर्ण
	हाल TAPE390_KEKL_SET:
		वापस tape_3592_ioctl_kekl_set(device, arg);
	हाल TAPE390_KEKL_QUERY:
		वापस tape_3592_ioctl_kekl_query(device, arg);
	हाल TAPE390_CRYPT_SET:
		वापस tape_3592_ioctl_crypt_set(device, arg);
	हाल TAPE390_CRYPT_QUERY:
		वापस tape_3592_ioctl_crypt_query(device, arg);
	शेष:
		वापस -EINVAL;	/* no additional ioctls */
	पूर्ण
पूर्ण

/*
 * SENSE Medium: Get Sense data about medium state
 */
अटल पूर्णांक tape_3590_sense_medium(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;

	request = tape_alloc_request(1, 128);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_MSEN;
	tape_ccw_end(request->cpaddr, MEDIUM_SENSE, 128, request->cpdata);
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

अटल व्योम tape_3590_sense_medium_async(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;

	request = tape_alloc_request(1, 128);
	अगर (IS_ERR(request))
		वापस;
	request->op = TO_MSEN;
	tape_ccw_end(request->cpaddr, MEDIUM_SENSE, 128, request->cpdata);
	tape_करो_io_async_मुक्त(device, request);
पूर्ण

/*
 * MTTELL: Tell block. Return the number of block relative to current file.
 */
अटल पूर्णांक
tape_3590_mttell(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	__u64 block_id;
	पूर्णांक rc;

	rc = tape_std_पढ़ो_block_id(device, &block_id);
	अगर (rc)
		वापस rc;
	वापस block_id >> 32;
पूर्ण

/*
 * MTSEEK: seek to the specअगरied block.
 */
अटल पूर्णांक
tape_3590_mtseek(काष्ठा tape_device *device, पूर्णांक count)
अणु
	काष्ठा tape_request *request;

	DBF_EVENT(6, "xsee id: %x\n", count);
	request = tape_alloc_request(3, 4);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_LBL;
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	*(__u32 *) request->cpdata = count;
	tape_ccw_cc(request->cpaddr + 1, LOCATE, 4, request->cpdata);
	tape_ccw_end(request->cpaddr + 2, NOP, 0, शून्य);
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * Read Opposite Error Recovery Function:
 * Used, when Read Forward करोes not work
 */
अटल व्योम
tape_3590_पढ़ो_opposite(काष्ठा tape_device *device,
			काष्ठा tape_request *request)
अणु
	काष्ठा tape_3590_disc_data *data;

	/*
	 * We have allocated 4 ccws in tape_std_पढ़ो, so we can now
	 * transक्रमm the request to a पढ़ो backward, followed by a
	 * क्रमward space block.
	 */
	request->op = TO_RBA;
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	data = device->discdata;
	tape_ccw_cc_idal(request->cpaddr + 1, data->पढ़ो_back_op,
			 device->अक्षर_data.idal_buf);
	tape_ccw_cc(request->cpaddr + 2, FORSPACEBLOCK, 0, शून्य);
	tape_ccw_end(request->cpaddr + 3, NOP, 0, शून्य);
	DBF_EVENT(6, "xrop ccwg\n");
पूर्ण

/*
 * Read Attention Msg
 * This should be करोne after an पूर्णांकerrupt with attention bit (0x80)
 * in device state.
 *
 * After a "read attention message" request there are two possible
 * results:
 *
 * 1. A unit check is presented, when attention sense is present (e.g. when
 * a medium has been unloaded). The attention sense comes then
 * together with the unit check. The recovery action is either "retry"
 * (in हाल there is an attention message pending) or "permanent error".
 *
 * 2. The attention msg is written to the "read subsystem data" buffer.
 * In this हाल we probably should prपूर्णांक it to the console.
 */
अटल व्योम tape_3590_पढ़ो_atपंचांगsg_async(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;
	अक्षर *buf;

	request = tape_alloc_request(3, 4096);
	अगर (IS_ERR(request))
		वापस;
	request->op = TO_READ_ATTMSG;
	buf = request->cpdata;
	buf[0] = PREP_RD_SS_DATA;
	buf[6] = RD_ATTMSG;	/* पढ़ो att msg */
	tape_ccw_cc(request->cpaddr, PERFORM_SS_FUNC, 12, buf);
	tape_ccw_cc(request->cpaddr + 1, READ_SS_DATA, 4096 - 12, buf + 12);
	tape_ccw_end(request->cpaddr + 2, NOP, 0, शून्य);
	tape_करो_io_async_मुक्त(device, request);
पूर्ण

/*
 * These functions are used to schedule follow-up actions from within an
 * पूर्णांकerrupt context (like unsolicited पूर्णांकerrupts).
 * Note: the work handler is called by the प्रणाली work queue. The tape
 * commands started by the handler need to be asynchrounous, otherwise
 * a deadlock can occur e.g. in हाल of a deferred cc=1 (see __tape_करो_irq).
 */
काष्ठा work_handler_data अणु
	काष्ठा tape_device *device;
	क्रमागत tape_op        op;
	काष्ठा work_काष्ठा  work;
पूर्ण;

अटल व्योम
tape_3590_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा work_handler_data *p =
		container_of(work, काष्ठा work_handler_data, work);

	चयन (p->op) अणु
	हाल TO_MSEN:
		tape_3590_sense_medium_async(p->device);
		अवरोध;
	हाल TO_READ_ATTMSG:
		tape_3590_पढ़ो_atपंचांगsg_async(p->device);
		अवरोध;
	हाल TO_CRYPT_ON:
		tape_3592_enable_crypt_async(p->device);
		अवरोध;
	हाल TO_CRYPT_OFF:
		tape_3592_disable_crypt_async(p->device);
		अवरोध;
	शेष:
		DBF_EVENT(3, "T3590: work handler undefined for "
			  "operation 0x%02x\n", p->op);
	पूर्ण
	tape_put_device(p->device);
	kमुक्त(p);
पूर्ण

अटल पूर्णांक
tape_3590_schedule_work(काष्ठा tape_device *device, क्रमागत tape_op op)
अणु
	काष्ठा work_handler_data *p;

	अगर ((p = kzalloc(माप(*p), GFP_ATOMIC)) == शून्य)
		वापस -ENOMEM;

	INIT_WORK(&p->work, tape_3590_work_handler);

	p->device = tape_get_device(device);
	p->op = op;

	queue_work(tape_3590_wq, &p->work);
	वापस 0;
पूर्ण

अटल व्योम tape_3590_med_state_set(काष्ठा tape_device *device,
				    काष्ठा tape_3590_med_sense *sense)
अणु
	काष्ठा tape390_crypt_info *c_info;

	c_info = &TAPE_3590_CRYPT_INFO(device);

	DBF_EVENT(6, "medium state: %x:%x\n", sense->macst, sense->masst);
	चयन (sense->macst) अणु
	हाल 0x04:
	हाल 0x05:
	हाल 0x06:
		tape_med_state_set(device, MS_UNLOADED);
		TAPE_3590_CRYPT_INFO(device).medium_status = 0;
		वापस;
	हाल 0x08:
	हाल 0x09:
		tape_med_state_set(device, MS_LOADED);
		अवरोध;
	शेष:
		tape_med_state_set(device, MS_UNKNOWN);
		वापस;
	पूर्ण
	c_info->medium_status |= TAPE390_MEDIUM_LOADED_MASK;
	अगर (sense->flags & MSENSE_CRYPT_MASK) अणु
		DBF_EVENT(6, "Medium is encrypted (%04x)\n", sense->flags);
		c_info->medium_status |= TAPE390_MEDIUM_ENCRYPTED_MASK;
	पूर्ण अन्यथा	अणु
		DBF_EVENT(6, "Medium is not encrypted %04x\n", sense->flags);
		c_info->medium_status &= ~TAPE390_MEDIUM_ENCRYPTED_MASK;
	पूर्ण
पूर्ण

/*
 * The करोne handler is called at device/channel end and wakes up the sleeping
 * process
 */
अटल पूर्णांक
tape_3590_करोne(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु

	DBF_EVENT(6, "%s done\n", tape_op_verbose[request->op]);

	चयन (request->op) अणु
	हाल TO_BSB:
	हाल TO_BSF:
	हाल TO_DSE:
	हाल TO_FSB:
	हाल TO_FSF:
	हाल TO_LBL:
	हाल TO_RFO:
	हाल TO_RBA:
	हाल TO_REW:
	हाल TO_WRI:
	हाल TO_WTM:
	हाल TO_BLOCK:
	हाल TO_LOAD:
		tape_med_state_set(device, MS_LOADED);
		अवरोध;
	हाल TO_RUN:
		tape_med_state_set(device, MS_UNLOADED);
		tape_3590_schedule_work(device, TO_CRYPT_OFF);
		अवरोध;
	हाल TO_MSEN:
		tape_3590_med_state_set(device, request->cpdata);
		अवरोध;
	हाल TO_CRYPT_ON:
		TAPE_3590_CRYPT_INFO(device).status
			|= TAPE390_CRYPT_ON_MASK;
		*(device->modeset_byte) |= 0x03;
		अवरोध;
	हाल TO_CRYPT_OFF:
		TAPE_3590_CRYPT_INFO(device).status
			&= ~TAPE390_CRYPT_ON_MASK;
		*(device->modeset_byte) &= ~0x03;
		अवरोध;
	हाल TO_RBI:	/* RBI seems to succeed even without medium loaded. */
	हाल TO_NOP:	/* Same to NOP. */
	हाल TO_READ_CONFIG:
	हाल TO_READ_ATTMSG:
	हाल TO_DIS:
	हाल TO_ASSIGN:
	हाल TO_UNASSIGN:
	हाल TO_SIZE:
	हाल TO_KEKL_SET:
	हाल TO_KEKL_QUERY:
	हाल TO_RDC:
		अवरोध;
	पूर्ण
	वापस TAPE_IO_SUCCESS;
पूर्ण

/*
 * This function is called, when error recovery was successful
 */
अटल अंतरभूत पूर्णांक
tape_3590_erp_succeeded(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	DBF_EVENT(3, "Error Recovery successful for %s\n",
		  tape_op_verbose[request->op]);
	वापस tape_3590_करोne(device, request);
पूर्ण

/*
 * This function is called, when error recovery was not successful
 */
अटल अंतरभूत पूर्णांक
tape_3590_erp_failed(काष्ठा tape_device *device, काष्ठा tape_request *request,
		     काष्ठा irb *irb, पूर्णांक rc)
अणु
	DBF_EVENT(3, "Error Recovery failed for %s\n",
		  tape_op_verbose[request->op]);
	tape_dump_sense_dbf(device, request, irb);
	वापस rc;
पूर्ण

/*
 * Error Recovery करो retry
 */
अटल अंतरभूत पूर्णांक
tape_3590_erp_retry(काष्ठा tape_device *device, काष्ठा tape_request *request,
		    काष्ठा irb *irb)
अणु
	DBF_EVENT(2, "Retry: %s\n", tape_op_verbose[request->op]);
	tape_dump_sense_dbf(device, request, irb);
	वापस TAPE_IO_RETRY;
पूर्ण

/*
 * Handle unsolicited पूर्णांकerrupts
 */
अटल पूर्णांक
tape_3590_unsolicited_irq(काष्ठा tape_device *device, काष्ठा irb *irb)
अणु
	अगर (irb->scsw.cmd.dstat == DEV_STAT_CHN_END)
		/* Probably result of halt ssch */
		वापस TAPE_IO_PENDING;
	अन्यथा अगर (irb->scsw.cmd.dstat == 0x85)
		/* Device Ready */
		DBF_EVENT(3, "unsol.irq! tape ready: %08x\n", device->cdev_id);
	अन्यथा अगर (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION) अणु
		tape_3590_schedule_work(device, TO_READ_ATTMSG);
	पूर्ण अन्यथा अणु
		DBF_EVENT(3, "unsol.irq! dev end: %08x\n", device->cdev_id);
		tape_dump_sense_dbf(device, शून्य, irb);
	पूर्ण
	/* check medium state */
	tape_3590_schedule_work(device, TO_MSEN);
	वापस TAPE_IO_SUCCESS;
पूर्ण

/*
 * Basic Recovery routine
 */
अटल पूर्णांक
tape_3590_erp_basic(काष्ठा tape_device *device, काष्ठा tape_request *request,
		    काष्ठा irb *irb, पूर्णांक rc)
अणु
	काष्ठा tape_3590_sense *sense;

	sense = (काष्ठा tape_3590_sense *) irb->ecw;

	चयन (sense->bra) अणु
	हाल SENSE_BRA_PER:
		वापस tape_3590_erp_failed(device, request, irb, rc);
	हाल SENSE_BRA_CONT:
		वापस tape_3590_erp_succeeded(device, request);
	हाल SENSE_BRA_RE:
		वापस tape_3590_erp_retry(device, request, irb);
	हाल SENSE_BRA_DRE:
		वापस tape_3590_erp_failed(device, request, irb, rc);
	शेष:
		BUG();
		वापस TAPE_IO_STOP;
	पूर्ण
पूर्ण

/*
 *  RDL: Read Device (buffered) log
 */
अटल पूर्णांक
tape_3590_erp_पढ़ो_buf_log(काष्ठा tape_device *device,
			   काष्ठा tape_request *request, काष्ठा irb *irb)
अणु
	/*
	 * We just करो the basic error recovery at the moment (retry).
	 * Perhaps in the future, we पढ़ो the log and dump it somewhere...
	 */
	वापस tape_3590_erp_basic(device, request, irb, -EIO);
पूर्ण

/*
 *  SWAP: Swap Devices
 */
अटल पूर्णांक
tape_3590_erp_swap(काष्ठा tape_device *device, काष्ठा tape_request *request,
		   काष्ठा irb *irb)
अणु
	/*
	 * This error recovery should swap the tapes
	 * अगर the original has a problem. The operation
	 * should proceed with the new tape... this
	 * should probably be करोne in user space!
	 */
	dev_warn (&device->cdev->dev, "The tape medium must be loaded into a "
		"different tape unit\n");
	वापस tape_3590_erp_basic(device, request, irb, -EIO);
पूर्ण

/*
 *  LBY: Long Busy
 */
अटल पूर्णांक
tape_3590_erp_दीर्घ_busy(काष्ठा tape_device *device,
			काष्ठा tape_request *request, काष्ठा irb *irb)
अणु
	DBF_EVENT(6, "Device is busy\n");
	वापस TAPE_IO_LONG_BUSY;
पूर्ण

/*
 *  SPI: Special Intercept
 */
अटल पूर्णांक
tape_3590_erp_special_पूर्णांकerrupt(काष्ठा tape_device *device,
				काष्ठा tape_request *request, काष्ठा irb *irb)
अणु
	वापस tape_3590_erp_basic(device, request, irb, -EIO);
पूर्ण

/*
 *  RDA: Read Alternate
 */
अटल पूर्णांक
tape_3590_erp_पढ़ो_alternate(काष्ठा tape_device *device,
			     काष्ठा tape_request *request, काष्ठा irb *irb)
अणु
	काष्ठा tape_3590_disc_data *data;

	/*
	 * The issued Read Backward or Read Previous command is not
	 * supported by the device
	 * The recovery action should be to issue another command:
	 * Read Revious: अगर Read Backward is not supported
	 * Read Backward: अगर Read Previous is not supported
	 */
	data = device->discdata;
	अगर (data->पढ़ो_back_op == READ_PREVIOUS) अणु
		DBF_EVENT(2, "(%08x): No support for READ_PREVIOUS command\n",
			  device->cdev_id);
		data->पढ़ो_back_op = READ_BACKWARD;
	पूर्ण अन्यथा अणु
		DBF_EVENT(2, "(%08x): No support for READ_BACKWARD command\n",
			  device->cdev_id);
		data->पढ़ो_back_op = READ_PREVIOUS;
	पूर्ण
	tape_3590_पढ़ो_opposite(device, request);
	वापस tape_3590_erp_retry(device, request, irb);
पूर्ण

/*
 * Error Recovery पढ़ो opposite
 */
अटल पूर्णांक
tape_3590_erp_पढ़ो_opposite(काष्ठा tape_device *device,
			    काष्ठा tape_request *request, काष्ठा irb *irb)
अणु
	चयन (request->op) अणु
	हाल TO_RFO:
		/*
		 * We did पढ़ो क्रमward, but the data could not be पढ़ो.
		 * We will पढ़ो backward and then skip क्रमward again.
		 */
		tape_3590_पढ़ो_opposite(device, request);
		वापस tape_3590_erp_retry(device, request, irb);
	हाल TO_RBA:
		/* We tried to पढ़ो क्रमward and backward, but hat no success */
		वापस tape_3590_erp_failed(device, request, irb, -EIO);
		अवरोध;
	शेष:
		वापस tape_3590_erp_failed(device, request, irb, -EIO);
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक an MIM (Media Inक्रमmation  Message) (message code f0)
 */
अटल व्योम
tape_3590_prपूर्णांक_mim_msg_f0(काष्ठा tape_device *device, काष्ठा irb *irb)
अणु
	काष्ठा tape_3590_sense *sense;
	अक्षर *exception, *service;

	exception = kदो_स्मृति(बफ_मानE, GFP_ATOMIC);
	service = kदो_स्मृति(बफ_मानE, GFP_ATOMIC);

	अगर (!exception || !service)
		जाओ out_nomem;

	sense = (काष्ठा tape_3590_sense *) irb->ecw;
	/* Exception Message */
	चयन (sense->fmt.f70.emc) अणु
	हाल 0x02:
		snम_लिखो(exception, बफ_मानE, "Data degraded");
		अवरोध;
	हाल 0x03:
		snम_लिखो(exception, बफ_मानE, "Data degraded in partition %i",
			sense->fmt.f70.mp);
		अवरोध;
	हाल 0x04:
		snम_लिखो(exception, बफ_मानE, "Medium degraded");
		अवरोध;
	हाल 0x05:
		snम_लिखो(exception, बफ_मानE, "Medium degraded in partition %i",
			sense->fmt.f70.mp);
		अवरोध;
	हाल 0x06:
		snम_लिखो(exception, बफ_मानE, "Block 0 Error");
		अवरोध;
	हाल 0x07:
		snम_लिखो(exception, बफ_मानE, "Medium Exception 0x%02x",
			sense->fmt.f70.md);
		अवरोध;
	शेष:
		snम_लिखो(exception, बफ_मानE, "0x%02x",
			sense->fmt.f70.emc);
		अवरोध;
	पूर्ण
	/* Service Message */
	चयन (sense->fmt.f70.smc) अणु
	हाल 0x02:
		snम_लिखो(service, बफ_मानE, "Reference Media maintenance "
			"procedure %i", sense->fmt.f70.md);
		अवरोध;
	शेष:
		snम_लिखो(service, बफ_मानE, "0x%02x",
			sense->fmt.f70.smc);
		अवरोध;
	पूर्ण

	dev_warn (&device->cdev->dev, "Tape media information: exception %s, "
		"service %s\n", exception, service);

out_nomem:
	kमुक्त(exception);
	kमुक्त(service);
पूर्ण

/*
 * Prपूर्णांक an I/O Subप्रणाली Service Inक्रमmation Message (message code f1)
 */
अटल व्योम
tape_3590_prपूर्णांक_io_sim_msg_f1(काष्ठा tape_device *device, काष्ठा irb *irb)
अणु
	काष्ठा tape_3590_sense *sense;
	अक्षर *exception, *service;

	exception = kदो_स्मृति(बफ_मानE, GFP_ATOMIC);
	service = kदो_स्मृति(बफ_मानE, GFP_ATOMIC);

	अगर (!exception || !service)
		जाओ out_nomem;

	sense = (काष्ठा tape_3590_sense *) irb->ecw;
	/* Exception Message */
	चयन (sense->fmt.f71.emc) अणु
	हाल 0x01:
		snम_लिखो(exception, बफ_मानE, "Effect of failure is unknown");
		अवरोध;
	हाल 0x02:
		snम_लिखो(exception, बफ_मानE, "CU Exception - no performance "
			"impact");
		अवरोध;
	हाल 0x03:
		snम_लिखो(exception, बफ_मानE, "CU Exception on channel "
			"interface 0x%02x", sense->fmt.f71.md[0]);
		अवरोध;
	हाल 0x04:
		snम_लिखो(exception, बफ_मानE, "CU Exception on device path "
			"0x%02x", sense->fmt.f71.md[0]);
		अवरोध;
	हाल 0x05:
		snम_लिखो(exception, बफ_मानE, "CU Exception on library path "
			"0x%02x", sense->fmt.f71.md[0]);
		अवरोध;
	हाल 0x06:
		snम_लिखो(exception, बफ_मानE, "CU Exception on node 0x%02x",
			sense->fmt.f71.md[0]);
		अवरोध;
	हाल 0x07:
		snम_लिखो(exception, बफ_मानE, "CU Exception on partition "
			"0x%02x", sense->fmt.f71.md[0]);
		अवरोध;
	शेष:
		snम_लिखो(exception, बफ_मानE, "0x%02x",
			sense->fmt.f71.emc);
	पूर्ण
	/* Service Message */
	चयन (sense->fmt.f71.smc) अणु
	हाल 0x01:
		snम_लिखो(service, बफ_मानE, "Repair impact is unknown");
		अवरोध;
	हाल 0x02:
		snम_लिखो(service, बफ_मानE, "Repair will not impact cu "
			"performance");
		अवरोध;
	हाल 0x03:
		अगर (sense->fmt.f71.mdf == 0)
			snम_लिखो(service, बफ_मानE, "Repair will disable node "
				"0x%x on CU", sense->fmt.f71.md[1]);
		अन्यथा
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"nodes (0x%x-0x%x) on CU", sense->fmt.f71.md[1],
				sense->fmt.f71.md[2]);
		अवरोध;
	हाल 0x04:
		अगर (sense->fmt.f71.mdf == 0)
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"channel path 0x%x on CU",
				sense->fmt.f71.md[1]);
		अन्यथा
			snम_लिखो(service, बफ_मानE, "Repair will disable channel"
				" paths (0x%x-0x%x) on CU",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		अवरोध;
	हाल 0x05:
		अगर (sense->fmt.f71.mdf == 0)
			snम_लिखो(service, बफ_मानE, "Repair will disable device"
				" path 0x%x on CU", sense->fmt.f71.md[1]);
		अन्यथा
			snम_लिखो(service, बफ_मानE, "Repair will disable device"
				" paths (0x%x-0x%x) on CU",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		अवरोध;
	हाल 0x06:
		अगर (sense->fmt.f71.mdf == 0)
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"library path 0x%x on CU",
				sense->fmt.f71.md[1]);
		अन्यथा
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"library paths (0x%x-0x%x) on CU",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		अवरोध;
	हाल 0x07:
		snम_लिखो(service, बफ_मानE, "Repair will disable access to CU");
		अवरोध;
	शेष:
		snम_लिखो(service, बफ_मानE, "0x%02x",
			sense->fmt.f71.smc);
	पूर्ण

	dev_warn (&device->cdev->dev, "I/O subsystem information: exception"
		" %s, service %s\n", exception, service);
out_nomem:
	kमुक्त(exception);
	kमुक्त(service);
पूर्ण

/*
 * Prपूर्णांक an Device Subप्रणाली Service Inक्रमmation Message (message code f2)
 */
अटल व्योम
tape_3590_prपूर्णांक_dev_sim_msg_f2(काष्ठा tape_device *device, काष्ठा irb *irb)
अणु
	काष्ठा tape_3590_sense *sense;
	अक्षर *exception, *service;

	exception = kदो_स्मृति(बफ_मानE, GFP_ATOMIC);
	service = kदो_स्मृति(बफ_मानE, GFP_ATOMIC);

	अगर (!exception || !service)
		जाओ out_nomem;

	sense = (काष्ठा tape_3590_sense *) irb->ecw;
	/* Exception Message */
	चयन (sense->fmt.f71.emc) अणु
	हाल 0x01:
		snम_लिखो(exception, बफ_मानE, "Effect of failure is unknown");
		अवरोध;
	हाल 0x02:
		snम_लिखो(exception, बफ_मानE, "DV Exception - no performance"
			" impact");
		अवरोध;
	हाल 0x03:
		snम_लिखो(exception, बफ_मानE, "DV Exception on channel "
			"interface 0x%02x", sense->fmt.f71.md[0]);
		अवरोध;
	हाल 0x04:
		snम_लिखो(exception, बफ_मानE, "DV Exception on loader 0x%02x",
			sense->fmt.f71.md[0]);
		अवरोध;
	हाल 0x05:
		snम_लिखो(exception, बफ_मानE, "DV Exception on message display"
			" 0x%02x", sense->fmt.f71.md[0]);
		अवरोध;
	हाल 0x06:
		snम_लिखो(exception, बफ_मानE, "DV Exception in tape path");
		अवरोध;
	हाल 0x07:
		snम_लिखो(exception, बफ_मानE, "DV Exception in drive");
		अवरोध;
	शेष:
		snम_लिखो(exception, बफ_मानE, "0x%02x",
			sense->fmt.f71.emc);
	पूर्ण
	/* Service Message */
	चयन (sense->fmt.f71.smc) अणु
	हाल 0x01:
		snम_लिखो(service, बफ_मानE, "Repair impact is unknown");
		अवरोध;
	हाल 0x02:
		snम_लिखो(service, बफ_मानE, "Repair will not impact device "
			"performance");
		अवरोध;
	हाल 0x03:
		अगर (sense->fmt.f71.mdf == 0)
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"channel path 0x%x on DV",
				sense->fmt.f71.md[1]);
		अन्यथा
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"channel path (0x%x-0x%x) on DV",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		अवरोध;
	हाल 0x04:
		अगर (sense->fmt.f71.mdf == 0)
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"interface 0x%x on DV", sense->fmt.f71.md[1]);
		अन्यथा
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"interfaces (0x%x-0x%x) on DV",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		अवरोध;
	हाल 0x05:
		अगर (sense->fmt.f71.mdf == 0)
			snम_लिखो(service, बफ_मानE, "Repair will disable loader"
				" 0x%x on DV", sense->fmt.f71.md[1]);
		अन्यथा
			snम_लिखो(service, बफ_मानE, "Repair will disable loader"
				" (0x%x-0x%x) on DV",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		अवरोध;
	हाल 0x07:
		snम_लिखो(service, बफ_मानE, "Repair will disable access to DV");
		अवरोध;
	हाल 0x08:
		अगर (sense->fmt.f71.mdf == 0)
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"message display 0x%x on DV",
				sense->fmt.f71.md[1]);
		अन्यथा
			snम_लिखो(service, बफ_मानE, "Repair will disable "
				"message displays (0x%x-0x%x) on DV",
				 sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		अवरोध;
	हाल 0x09:
		snम_लिखो(service, बफ_मानE, "Clean DV");
		अवरोध;
	शेष:
		snम_लिखो(service, बफ_मानE, "0x%02x",
			sense->fmt.f71.smc);
	पूर्ण

	dev_warn (&device->cdev->dev, "Device subsystem information: exception"
		" %s, service %s\n", exception, service);
out_nomem:
	kमुक्त(exception);
	kमुक्त(service);
पूर्ण

/*
 * Prपूर्णांक standard ERA Message
 */
अटल व्योम
tape_3590_prपूर्णांक_era_msg(काष्ठा tape_device *device, काष्ठा irb *irb)
अणु
	काष्ठा tape_3590_sense *sense;

	sense = (काष्ठा tape_3590_sense *) irb->ecw;
	अगर (sense->mc == 0)
		वापस;
	अगर ((sense->mc > 0) && (sense->mc < TAPE_3590_MAX_MSG)) अणु
		अगर (tape_3590_msg[sense->mc] != शून्य)
			dev_warn (&device->cdev->dev, "The tape unit has "
				"issued sense message %s\n",
				tape_3590_msg[sense->mc]);
		अन्यथा
			dev_warn (&device->cdev->dev, "The tape unit has "
				"issued an unknown sense message code 0x%x\n",
				sense->mc);
		वापस;
	पूर्ण
	अगर (sense->mc == 0xf0) अणु
		/* Standard Media Inक्रमmation Message */
		dev_warn (&device->cdev->dev, "MIM SEV=%i, MC=%02x, ES=%x/%x, "
			"RC=%02x-%04x-%02x\n", sense->fmt.f70.sev, sense->mc,
			sense->fmt.f70.emc, sense->fmt.f70.smc,
			sense->fmt.f70.refcode, sense->fmt.f70.mid,
			sense->fmt.f70.fid);
		tape_3590_prपूर्णांक_mim_msg_f0(device, irb);
		वापस;
	पूर्ण
	अगर (sense->mc == 0xf1) अणु
		/* Standard I/O Subप्रणाली Service Inक्रमmation Message */
		dev_warn (&device->cdev->dev, "IOSIM SEV=%i, DEVTYPE=3590/%02x,"
			" MC=%02x, ES=%x/%x, REF=0x%04x-0x%04x-0x%04x\n",
			sense->fmt.f71.sev, device->cdev->id.dev_model,
			sense->mc, sense->fmt.f71.emc, sense->fmt.f71.smc,
			sense->fmt.f71.refcode1, sense->fmt.f71.refcode2,
			sense->fmt.f71.refcode3);
		tape_3590_prपूर्णांक_io_sim_msg_f1(device, irb);
		वापस;
	पूर्ण
	अगर (sense->mc == 0xf2) अणु
		/* Standard Device Service Inक्रमmation Message */
		dev_warn (&device->cdev->dev, "DEVSIM SEV=%i, DEVTYPE=3590/%02x"
			", MC=%02x, ES=%x/%x, REF=0x%04x-0x%04x-0x%04x\n",
			sense->fmt.f71.sev, device->cdev->id.dev_model,
			sense->mc, sense->fmt.f71.emc, sense->fmt.f71.smc,
			sense->fmt.f71.refcode1, sense->fmt.f71.refcode2,
			sense->fmt.f71.refcode3);
		tape_3590_prपूर्णांक_dev_sim_msg_f2(device, irb);
		वापस;
	पूर्ण
	अगर (sense->mc == 0xf3) अणु
		/* Standard Library Service Inक्रमmation Message */
		वापस;
	पूर्ण
	dev_warn (&device->cdev->dev, "The tape unit has issued an unknown "
		"sense message code %x\n", sense->mc);
पूर्ण

अटल पूर्णांक tape_3590_crypt_error(काष्ठा tape_device *device,
				 काष्ठा tape_request *request, काष्ठा irb *irb)
अणु
	u8 cu_rc;
	u16 ekm_rc2;
	अक्षर *sense;

	sense = ((काष्ठा tape_3590_sense *) irb->ecw)->fmt.data;
	cu_rc = sense[0];
	ekm_rc2 = *((u16*) &sense[10]);
	अगर ((cu_rc == 0) && (ekm_rc2 == 0xee31))
		/* key not defined on EKM */
		वापस tape_3590_erp_basic(device, request, irb, -EKEYREJECTED);
	अगर ((cu_rc == 1) || (cu_rc == 2))
		/* No connection to EKM */
		वापस tape_3590_erp_basic(device, request, irb, -ENOTCONN);

	dev_err (&device->cdev->dev, "The tape unit failed to obtain the "
		"encryption key from EKM\n");

	वापस tape_3590_erp_basic(device, request, irb, -ENOKEY);
पूर्ण

/*
 *  3590 error Recovery routine:
 *  If possible, it tries to recover from the error. If this is not possible,
 *  inक्रमm the user about the problem.
 */
अटल पूर्णांक
tape_3590_unit_check(काष्ठा tape_device *device, काष्ठा tape_request *request,
		     काष्ठा irb *irb)
अणु
	काष्ठा tape_3590_sense *sense;

	sense = (काष्ठा tape_3590_sense *) irb->ecw;

	DBF_EVENT(6, "Unit Check: RQC = %x\n", sense->rc_rqc);

	/*
	 * First check all RC-QRCs where we want to करो something special
	 *   - "break":     basic error recovery is करोne
	 *   - "goto out:": just prपूर्णांक error message अगर available
	 */
	चयन (sense->rc_rqc) अणु

	हाल 0x1110:
		tape_3590_prपूर्णांक_era_msg(device, irb);
		वापस tape_3590_erp_पढ़ो_buf_log(device, request, irb);

	हाल 0x2011:
		tape_3590_prपूर्णांक_era_msg(device, irb);
		वापस tape_3590_erp_पढ़ो_alternate(device, request, irb);

	हाल 0x2230:
	हाल 0x2231:
		tape_3590_prपूर्णांक_era_msg(device, irb);
		वापस tape_3590_erp_special_पूर्णांकerrupt(device, request, irb);
	हाल 0x2240:
		वापस tape_3590_crypt_error(device, request, irb);

	हाल 0x3010:
		DBF_EVENT(2, "(%08x): Backward at Beginning of Partition\n",
			  device->cdev_id);
		वापस tape_3590_erp_basic(device, request, irb, -ENOSPC);
	हाल 0x3012:
		DBF_EVENT(2, "(%08x): Forward at End of Partition\n",
			  device->cdev_id);
		वापस tape_3590_erp_basic(device, request, irb, -ENOSPC);
	हाल 0x3020:
		DBF_EVENT(2, "(%08x): End of Data Mark\n", device->cdev_id);
		वापस tape_3590_erp_basic(device, request, irb, -ENOSPC);

	हाल 0x3122:
		DBF_EVENT(2, "(%08x): Rewind Unload initiated\n",
			  device->cdev_id);
		वापस tape_3590_erp_basic(device, request, irb, -EIO);
	हाल 0x3123:
		DBF_EVENT(2, "(%08x): Rewind Unload complete\n",
			  device->cdev_id);
		tape_med_state_set(device, MS_UNLOADED);
		tape_3590_schedule_work(device, TO_CRYPT_OFF);
		वापस tape_3590_erp_basic(device, request, irb, 0);

	हाल 0x4010:
		/*
		 * prपूर्णांक additional msg since शेष msg
		 * "device intervention" is not very meaningfull
		 */
		tape_med_state_set(device, MS_UNLOADED);
		tape_3590_schedule_work(device, TO_CRYPT_OFF);
		वापस tape_3590_erp_basic(device, request, irb, -ENOMEDIUM);
	हाल 0x4012:		/* Device Long Busy */
		/* XXX: Also use दीर्घ busy handling here? */
		DBF_EVENT(6, "(%08x): LONG BUSY\n", device->cdev_id);
		tape_3590_prपूर्णांक_era_msg(device, irb);
		वापस tape_3590_erp_basic(device, request, irb, -EBUSY);
	हाल 0x4014:
		DBF_EVENT(6, "(%08x): Crypto LONG BUSY\n", device->cdev_id);
		वापस tape_3590_erp_दीर्घ_busy(device, request, irb);

	हाल 0x5010:
		अगर (sense->rac == 0xd0) अणु
			/* Swap */
			tape_3590_prपूर्णांक_era_msg(device, irb);
			वापस tape_3590_erp_swap(device, request, irb);
		पूर्ण
		अगर (sense->rac == 0x26) अणु
			/* Read Opposite */
			tape_3590_prपूर्णांक_era_msg(device, irb);
			वापस tape_3590_erp_पढ़ो_opposite(device, request,
							   irb);
		पूर्ण
		वापस tape_3590_erp_basic(device, request, irb, -EIO);
	हाल 0x5020:
	हाल 0x5021:
	हाल 0x5022:
	हाल 0x5040:
	हाल 0x5041:
	हाल 0x5042:
		tape_3590_prपूर्णांक_era_msg(device, irb);
		वापस tape_3590_erp_swap(device, request, irb);

	हाल 0x5110:
	हाल 0x5111:
		वापस tape_3590_erp_basic(device, request, irb, -EMEDIUMTYPE);

	हाल 0x5120:
	हाल 0x1120:
		tape_med_state_set(device, MS_UNLOADED);
		tape_3590_schedule_work(device, TO_CRYPT_OFF);
		वापस tape_3590_erp_basic(device, request, irb, -ENOMEDIUM);

	हाल 0x6020:
		वापस tape_3590_erp_basic(device, request, irb, -EMEDIUMTYPE);

	हाल 0x8011:
		वापस tape_3590_erp_basic(device, request, irb, -EPERM);
	हाल 0x8013:
		dev_warn (&device->cdev->dev, "A different host has privileged"
			" access to the tape unit\n");
		वापस tape_3590_erp_basic(device, request, irb, -EPERM);
	शेष:
		वापस tape_3590_erp_basic(device, request, irb, -EIO);
	पूर्ण
पूर्ण

/*
 * 3590 पूर्णांकerrupt handler:
 */
अटल पूर्णांक
tape_3590_irq(काष्ठा tape_device *device, काष्ठा tape_request *request,
	      काष्ठा irb *irb)
अणु
	अगर (request == शून्य)
		वापस tape_3590_unsolicited_irq(device, irb);

	अगर ((irb->scsw.cmd.dstat & DEV_STAT_UNIT_EXCEP) &&
	    (irb->scsw.cmd.dstat & DEV_STAT_DEV_END) &&
	    (request->op == TO_WRI)) अणु
		/* Write at end of volume */
		DBF_EVENT(2, "End of volume\n");
		वापस tape_3590_erp_failed(device, request, irb, -ENOSPC);
	पूर्ण

	अगर (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)
		वापस tape_3590_unit_check(device, request, irb);

	अगर (irb->scsw.cmd.dstat & DEV_STAT_DEV_END) अणु
		अगर (irb->scsw.cmd.dstat == DEV_STAT_UNIT_EXCEP) अणु
			अगर (request->op == TO_FSB || request->op == TO_BSB)
				request->rescnt++;
			अन्यथा
				DBF_EVENT(5, "Unit Exception!\n");
		पूर्ण

		वापस tape_3590_करोne(device, request);
	पूर्ण

	अगर (irb->scsw.cmd.dstat & DEV_STAT_CHN_END) अणु
		DBF_EVENT(2, "channel end\n");
		वापस TAPE_IO_PENDING;
	पूर्ण

	अगर (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION) अणु
		DBF_EVENT(2, "Unit Attention when busy..\n");
		वापस TAPE_IO_PENDING;
	पूर्ण

	DBF_EVENT(6, "xunknownirq\n");
	tape_dump_sense_dbf(device, request, irb);
	वापस TAPE_IO_STOP;
पूर्ण


अटल पूर्णांक tape_3590_पढ़ो_dev_अक्षरs(काष्ठा tape_device *device,
				    काष्ठा tape_3590_rdc_data *rdc_data)
अणु
	पूर्णांक rc;
	काष्ठा tape_request *request;

	request = tape_alloc_request(1, माप(*rdc_data));
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_RDC;
	tape_ccw_end(request->cpaddr, CCW_CMD_RDC, माप(*rdc_data),
		     request->cpdata);
	rc = tape_करो_io(device, request);
	अगर (rc == 0)
		स_नकल(rdc_data, request->cpdata, माप(*rdc_data));
	tape_मुक्त_request(request);
	वापस rc;
पूर्ण

/*
 * Setup device function
 */
अटल पूर्णांक
tape_3590_setup_device(काष्ठा tape_device *device)
अणु
	पूर्णांक rc;
	काष्ठा tape_3590_disc_data *data;
	काष्ठा tape_3590_rdc_data *rdc_data;

	DBF_EVENT(6, "3590 device setup\n");
	data = kzalloc(माप(काष्ठा tape_3590_disc_data), GFP_KERNEL | GFP_DMA);
	अगर (data == शून्य)
		वापस -ENOMEM;
	data->पढ़ो_back_op = READ_PREVIOUS;
	device->discdata = data;

	rdc_data = kदो_स्मृति(माप(*rdc_data), GFP_KERNEL | GFP_DMA);
	अगर (!rdc_data) अणु
		rc = -ENOMEM;
		जाओ fail_kदो_स्मृति;
	पूर्ण
	rc = tape_3590_पढ़ो_dev_अक्षरs(device, rdc_data);
	अगर (rc) अणु
		DBF_LH(3, "Read device characteristics failed!\n");
		जाओ fail_rdc_data;
	पूर्ण
	rc = tape_std_assign(device);
	अगर (rc)
		जाओ fail_rdc_data;
	अगर (rdc_data->data[31] == 0x13) अणु
		data->crypt_info.capability |= TAPE390_CRYPT_SUPPORTED_MASK;
		tape_3592_disable_crypt(device);
	पूर्ण अन्यथा अणु
		DBF_EVENT(6, "Device has NO crypto support\n");
	पूर्ण
	/* Try to find out अगर medium is loaded */
	rc = tape_3590_sense_medium(device);
	अगर (rc) अणु
		DBF_LH(3, "3590 medium sense returned %d\n", rc);
		जाओ fail_rdc_data;
	पूर्ण
	वापस 0;

fail_rdc_data:
	kमुक्त(rdc_data);
fail_kदो_स्मृति:
	kमुक्त(data);
	वापस rc;
पूर्ण

/*
 * Cleanup device function
 */
अटल व्योम
tape_3590_cleanup_device(काष्ठा tape_device *device)
अणु
	flush_workqueue(tape_3590_wq);
	tape_std_unassign(device);

	kमुक्त(device->discdata);
	device->discdata = शून्य;
पूर्ण

/*
 * List of 3590 magnetic tape commands.
 */
अटल tape_mtop_fn tape_3590_mtop[TAPE_NR_MTOPS] = अणु
	[MTRESET]	 = tape_std_mtreset,
	[MTFSF]		 = tape_std_mtfsf,
	[MTBSF]		 = tape_std_mtbsf,
	[MTFSR]		 = tape_std_mtfsr,
	[MTBSR]		 = tape_std_mtbsr,
	[MTWखातापूर्ण]	 = tape_std_mtweof,
	[MTREW]		 = tape_std_mtrew,
	[MTOFFL]	 = tape_std_mtoffl,
	[MTNOP]		 = tape_std_mtnop,
	[MTRETEN]	 = tape_std_mtreten,
	[MTBSFM]	 = tape_std_mtbsfm,
	[MTFSFM]	 = tape_std_mtfsfm,
	[MTEOM]		 = tape_std_mteom,
	[MTERASE]	 = tape_std_mterase,
	[MTRAS1]	 = शून्य,
	[MTRAS2]	 = शून्य,
	[MTRAS3]	 = शून्य,
	[MTSETBLK]	 = tape_std_mtsetblk,
	[MTSETDENSITY]	 = शून्य,
	[MTSEEK]	 = tape_3590_mtseek,
	[MTTELL]	 = tape_3590_mttell,
	[MTSETDRVBUFFER] = शून्य,
	[MTFSS]		 = शून्य,
	[MTBSS]		 = शून्य,
	[MTWSM]		 = शून्य,
	[MTLOCK]	 = शून्य,
	[MTUNLOCK]	 = शून्य,
	[MTLOAD]	 = tape_std_mtload,
	[MTUNLOAD]	 = tape_std_mtunload,
	[MTCOMPRESSION]	 = tape_std_mtcompression,
	[MTSETPART]	 = शून्य,
	[MTMKPART]	 = शून्य
पूर्ण;

/*
 * Tape discipline काष्ठाure क्रम 3590.
 */
अटल काष्ठा tape_discipline tape_discipline_3590 = अणु
	.owner = THIS_MODULE,
	.setup_device = tape_3590_setup_device,
	.cleanup_device = tape_3590_cleanup_device,
	.process_eov = tape_std_process_eov,
	.irq = tape_3590_irq,
	.पढ़ो_block = tape_std_पढ़ो_block,
	.ग_लिखो_block = tape_std_ग_लिखो_block,
	.ioctl_fn = tape_3590_ioctl,
	.mtop_array = tape_3590_mtop
पूर्ण;

अटल काष्ठा ccw_device_id tape_3590_ids[] = अणु
	अणुCCW_DEVICE_DEVTYPE(0x3590, 0, 0x3590, 0), .driver_info = tape_3590पूर्ण,
	अणुCCW_DEVICE_DEVTYPE(0x3592, 0, 0x3592, 0), .driver_info = tape_3592पूर्ण,
	अणु /* end of list */ पूर्ण
पूर्ण;

अटल पूर्णांक
tape_3590_online(काष्ठा ccw_device *cdev)
अणु
	वापस tape_generic_online(dev_get_drvdata(&cdev->dev),
				   &tape_discipline_3590);
पूर्ण

अटल काष्ठा ccw_driver tape_3590_driver = अणु
	.driver = अणु
		.name = "tape_3590",
		.owner = THIS_MODULE,
	पूर्ण,
	.ids = tape_3590_ids,
	.probe = tape_generic_probe,
	.हटाओ = tape_generic_हटाओ,
	.set_offline = tape_generic_offline,
	.set_online = tape_3590_online,
	.पूर्णांक_class = IRQIO_TAP,
पूर्ण;

/*
 * Setup discipline काष्ठाure.
 */
अटल पूर्णांक
tape_3590_init(व्योम)
अणु
	पूर्णांक rc;

	TAPE_DBF_AREA = debug_रेजिस्टर("tape_3590", 2, 2, 4 * माप(दीर्घ));
	debug_रेजिस्टर_view(TAPE_DBF_AREA, &debug_प्र_लिखो_view);
#अगर_घोषित DBF_LIKE_HELL
	debug_set_level(TAPE_DBF_AREA, 6);
#पूर्ण_अगर

	DBF_EVENT(3, "3590 init\n");

	tape_3590_wq = alloc_workqueue("tape_3590", 0, 0);
	अगर (!tape_3590_wq)
		वापस -ENOMEM;

	/* Register driver क्रम 3590 tapes. */
	rc = ccw_driver_रेजिस्टर(&tape_3590_driver);
	अगर (rc) अणु
		destroy_workqueue(tape_3590_wq);
		DBF_EVENT(3, "3590 init failed\n");
	पूर्ण अन्यथा
		DBF_EVENT(3, "3590 registered\n");
	वापस rc;
पूर्ण

अटल व्योम
tape_3590_निकास(व्योम)
अणु
	ccw_driver_unरेजिस्टर(&tape_3590_driver);
	destroy_workqueue(tape_3590_wq);
	debug_unरेजिस्टर(TAPE_DBF_AREA);
पूर्ण

MODULE_DEVICE_TABLE(ccw, tape_3590_ids);
MODULE_AUTHOR("(C) 2001,2006 IBM Corporation");
MODULE_DESCRIPTION("Linux on zSeries channel attached 3590 tape device driver");
MODULE_LICENSE("GPL");

module_init(tape_3590_init);
module_निकास(tape_3590_निकास);
