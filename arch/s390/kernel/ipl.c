<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    ipl/reipl/dump support क्रम Linux on s390.
 *
 *    Copyright IBM Corp. 2005, 2012
 *    Author(s): Michael Holzheu <holzheu@de.ibm.com>
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>
 *		 Volker Sameske <sameske@de.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/reboot.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/debug_locks.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/checksum.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/os_info.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/boot_data.h>
#समावेश "entry.h"

#घोषणा IPL_PARM_BLOCK_VERSION 0

#घोषणा IPL_UNKNOWN_STR		"unknown"
#घोषणा IPL_CCW_STR		"ccw"
#घोषणा IPL_FCP_STR		"fcp"
#घोषणा IPL_FCP_DUMP_STR	"fcp_dump"
#घोषणा IPL_NVME_STR		"nvme"
#घोषणा IPL_NVME_DUMP_STR	"nvme_dump"
#घोषणा IPL_NSS_STR		"nss"

#घोषणा DUMP_CCW_STR		"ccw"
#घोषणा DUMP_FCP_STR		"fcp"
#घोषणा DUMP_NVME_STR		"nvme"
#घोषणा DUMP_NONE_STR		"none"

/*
 * Four shutकरोwn trigger types are supported:
 * - panic
 * - halt
 * - घातer off
 * - reipl
 * - restart
 */
#घोषणा ON_PANIC_STR		"on_panic"
#घोषणा ON_HALT_STR		"on_halt"
#घोषणा ON_POFF_STR		"on_poff"
#घोषणा ON_REIPL_STR		"on_reboot"
#घोषणा ON_RESTART_STR		"on_restart"

काष्ठा shutकरोwn_action;
काष्ठा shutकरोwn_trigger अणु
	अक्षर *name;
	काष्ठा shutकरोwn_action *action;
पूर्ण;

/*
 * The following shutकरोwn action types are supported:
 */
#घोषणा SHUTDOWN_ACTION_IPL_STR		"ipl"
#घोषणा SHUTDOWN_ACTION_REIPL_STR	"reipl"
#घोषणा SHUTDOWN_ACTION_DUMP_STR	"dump"
#घोषणा SHUTDOWN_ACTION_VMCMD_STR	"vmcmd"
#घोषणा SHUTDOWN_ACTION_STOP_STR	"stop"
#घोषणा SHUTDOWN_ACTION_DUMP_REIPL_STR	"dump_reipl"

काष्ठा shutकरोwn_action अणु
	अक्षर *name;
	व्योम (*fn) (काष्ठा shutकरोwn_trigger *trigger);
	पूर्णांक (*init) (व्योम);
	पूर्णांक init_rc;
पूर्ण;

अटल अक्षर *ipl_type_str(क्रमागत ipl_type type)
अणु
	चयन (type) अणु
	हाल IPL_TYPE_CCW:
		वापस IPL_CCW_STR;
	हाल IPL_TYPE_FCP:
		वापस IPL_FCP_STR;
	हाल IPL_TYPE_FCP_DUMP:
		वापस IPL_FCP_DUMP_STR;
	हाल IPL_TYPE_NSS:
		वापस IPL_NSS_STR;
	हाल IPL_TYPE_NVME:
		वापस IPL_NVME_STR;
	हाल IPL_TYPE_NVME_DUMP:
		वापस IPL_NVME_DUMP_STR;
	हाल IPL_TYPE_UNKNOWN:
	शेष:
		वापस IPL_UNKNOWN_STR;
	पूर्ण
पूर्ण

क्रमागत dump_type अणु
	DUMP_TYPE_NONE	= 1,
	DUMP_TYPE_CCW	= 2,
	DUMP_TYPE_FCP	= 4,
	DUMP_TYPE_NVME	= 8,
पूर्ण;

अटल अक्षर *dump_type_str(क्रमागत dump_type type)
अणु
	चयन (type) अणु
	हाल DUMP_TYPE_NONE:
		वापस DUMP_NONE_STR;
	हाल DUMP_TYPE_CCW:
		वापस DUMP_CCW_STR;
	हाल DUMP_TYPE_FCP:
		वापस DUMP_FCP_STR;
	हाल DUMP_TYPE_NVME:
		वापस DUMP_NVME_STR;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

पूर्णांक __bootdata_preserved(ipl_block_valid);
काष्ठा ipl_parameter_block __bootdata_preserved(ipl_block);
पूर्णांक __bootdata_preserved(ipl_secure_flag);

अचिन्हित दीर्घ __bootdata_preserved(ipl_cert_list_addr);
अचिन्हित दीर्घ __bootdata_preserved(ipl_cert_list_size);

अचिन्हित दीर्घ __bootdata(early_ipl_comp_list_addr);
अचिन्हित दीर्घ __bootdata(early_ipl_comp_list_size);

अटल पूर्णांक reipl_capabilities = IPL_TYPE_UNKNOWN;

अटल क्रमागत ipl_type reipl_type = IPL_TYPE_UNKNOWN;
अटल काष्ठा ipl_parameter_block *reipl_block_fcp;
अटल काष्ठा ipl_parameter_block *reipl_block_nvme;
अटल काष्ठा ipl_parameter_block *reipl_block_ccw;
अटल काष्ठा ipl_parameter_block *reipl_block_nss;
अटल काष्ठा ipl_parameter_block *reipl_block_actual;

अटल पूर्णांक dump_capabilities = DUMP_TYPE_NONE;
अटल क्रमागत dump_type dump_type = DUMP_TYPE_NONE;
अटल काष्ठा ipl_parameter_block *dump_block_fcp;
अटल काष्ठा ipl_parameter_block *dump_block_nvme;
अटल काष्ठा ipl_parameter_block *dump_block_ccw;

अटल काष्ठा sclp_ipl_info sclp_ipl_info;

अटल bool reipl_nvme_clear;
अटल bool reipl_fcp_clear;
अटल bool reipl_ccw_clear;

अटल अंतरभूत पूर्णांक __diag308(अचिन्हित दीर्घ subcode, व्योम *addr)
अणु
	रेजिस्टर अचिन्हित दीर्घ _addr यंत्र("0") = (अचिन्हित दीर्घ) addr;
	रेजिस्टर अचिन्हित दीर्घ _rc यंत्र("1") = 0;

	यंत्र अस्थिर(
		"	diag	%0,%2,0x308\n"
		"0:	nopr	%%r7\n"
		EX_TABLE(0b,0b)
		: "+d" (_addr), "+d" (_rc)
		: "d" (subcode) : "cc", "memory");
	वापस _rc;
पूर्ण

पूर्णांक diag308(अचिन्हित दीर्घ subcode, व्योम *addr)
अणु
	अगर (IS_ENABLED(CONFIG_KASAN))
		__arch_local_irq_stosm(0x04); /* enable DAT */
	diag_stat_inc(DIAG_STAT_X308);
	वापस __diag308(subcode, addr);
पूर्ण
EXPORT_SYMBOL_GPL(diag308);

/* SYSFS */

#घोषणा IPL_ATTR_SHOW_FN(_prefix, _name, _क्रमmat, args...)		\
अटल sमाप_प्रकार sys_##_prefix##_##_name##_show(काष्ठा kobject *kobj,	\
		काष्ठा kobj_attribute *attr,				\
		अक्षर *page)						\
अणु									\
	वापस scnम_लिखो(page, PAGE_SIZE, _क्रमmat, ##args);		\
पूर्ण

#घोषणा IPL_ATTR_CCW_STORE_FN(_prefix, _name, _ipl_blk)			\
अटल sमाप_प्रकार sys_##_prefix##_##_name##_store(काष्ठा kobject *kobj,	\
		काष्ठा kobj_attribute *attr,				\
		स्थिर अक्षर *buf, माप_प्रकार len)				\
अणु									\
	अचिन्हित दीर्घ दीर्घ ssid, devno;					\
									\
	अगर (माला_पूछो(buf, "0.%llx.%llx\n", &ssid, &devno) != 2)		\
		वापस -EINVAL;						\
									\
	अगर (ssid > __MAX_SSID || devno > __MAX_SUBCHANNEL)		\
		वापस -EINVAL;						\
									\
	_ipl_blk.ssid = ssid;						\
	_ipl_blk.devno = devno;						\
	वापस len;							\
पूर्ण

#घोषणा DEFINE_IPL_CCW_ATTR_RW(_prefix, _name, _ipl_blk)		\
IPL_ATTR_SHOW_FN(_prefix, _name, "0.%x.%04x\n",				\
		 _ipl_blk.ssid, _ipl_blk.devno);			\
IPL_ATTR_CCW_STORE_FN(_prefix, _name, _ipl_blk);			\
अटल काष्ठा kobj_attribute sys_##_prefix##_##_name##_attr =		\
	__ATTR(_name, (S_IRUGO | S_IWUSR),				\
	       sys_##_prefix##_##_name##_show,				\
	       sys_##_prefix##_##_name##_store)				\

#घोषणा DEFINE_IPL_ATTR_RO(_prefix, _name, _क्रमmat, _value)		\
IPL_ATTR_SHOW_FN(_prefix, _name, _क्रमmat, _value)			\
अटल काष्ठा kobj_attribute sys_##_prefix##_##_name##_attr =		\
	__ATTR(_name, S_IRUGO, sys_##_prefix##_##_name##_show, शून्य)

#घोषणा DEFINE_IPL_ATTR_RW(_prefix, _name, _fmt_out, _fmt_in, _value)	\
IPL_ATTR_SHOW_FN(_prefix, _name, _fmt_out, (अचिन्हित दीर्घ दीर्घ) _value)	\
अटल sमाप_प्रकार sys_##_prefix##_##_name##_store(काष्ठा kobject *kobj,	\
		काष्ठा kobj_attribute *attr,				\
		स्थिर अक्षर *buf, माप_प्रकार len)				\
अणु									\
	अचिन्हित दीर्घ दीर्घ value;					\
	अगर (माला_पूछो(buf, _fmt_in, &value) != 1)				\
		वापस -EINVAL;						\
	_value = value;							\
	वापस len;							\
पूर्ण									\
अटल काष्ठा kobj_attribute sys_##_prefix##_##_name##_attr =		\
	__ATTR(_name,(S_IRUGO | S_IWUSR),				\
			sys_##_prefix##_##_name##_show,			\
			sys_##_prefix##_##_name##_store)

#घोषणा DEFINE_IPL_ATTR_STR_RW(_prefix, _name, _fmt_out, _fmt_in, _value)\
IPL_ATTR_SHOW_FN(_prefix, _name, _fmt_out, _value)			\
अटल sमाप_प्रकार sys_##_prefix##_##_name##_store(काष्ठा kobject *kobj,	\
		काष्ठा kobj_attribute *attr,				\
		स्थिर अक्षर *buf, माप_प्रकार len)				\
अणु									\
	म_नकलन(_value, buf, माप(_value) - 1);			\
	strim(_value);							\
	वापस len;							\
पूर्ण									\
अटल काष्ठा kobj_attribute sys_##_prefix##_##_name##_attr =		\
	__ATTR(_name,(S_IRUGO | S_IWUSR),				\
			sys_##_prefix##_##_name##_show,			\
			sys_##_prefix##_##_name##_store)

/*
 * ipl section
 */

अटल __init क्रमागत ipl_type get_ipl_type(व्योम)
अणु
	अगर (!ipl_block_valid)
		वापस IPL_TYPE_UNKNOWN;

	चयन (ipl_block.pb0_hdr.pbt) अणु
	हाल IPL_PBT_CCW:
		वापस IPL_TYPE_CCW;
	हाल IPL_PBT_FCP:
		अगर (ipl_block.fcp.opt == IPL_PB0_FCP_OPT_DUMP)
			वापस IPL_TYPE_FCP_DUMP;
		अन्यथा
			वापस IPL_TYPE_FCP;
	हाल IPL_PBT_NVME:
		अगर (ipl_block.nvme.opt == IPL_PB0_NVME_OPT_DUMP)
			वापस IPL_TYPE_NVME_DUMP;
		अन्यथा
			वापस IPL_TYPE_NVME;
	पूर्ण
	वापस IPL_TYPE_UNKNOWN;
पूर्ण

काष्ठा ipl_info ipl_info;
EXPORT_SYMBOL_GPL(ipl_info);

अटल sमाप_प्रकार ipl_type_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			     अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", ipl_type_str(ipl_info.type));
पूर्ण

अटल काष्ठा kobj_attribute sys_ipl_type_attr = __ATTR_RO(ipl_type);

अटल sमाप_प्रकार ipl_secure_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%i\n", !!ipl_secure_flag);
पूर्ण

अटल काष्ठा kobj_attribute sys_ipl_secure_attr =
	__ATTR(secure, 0444, ipl_secure_show, शून्य);

अटल sमाप_प्रकार ipl_has_secure_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%i\n", !!sclp.has_sipl);
पूर्ण

अटल काष्ठा kobj_attribute sys_ipl_has_secure_attr =
	__ATTR(has_secure, 0444, ipl_has_secure_show, शून्य);

अटल sमाप_प्रकार ipl_vm_parm_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	अक्षर parm[DIAG308_VMPARM_SIZE + 1] = अणुपूर्ण;

	अगर (ipl_block_valid && (ipl_block.pb0_hdr.pbt == IPL_PBT_CCW))
		ipl_block_get_ascii_vmparm(parm, माप(parm), &ipl_block);
	वापस प्र_लिखो(page, "%s\n", parm);
पूर्ण

अटल काष्ठा kobj_attribute sys_ipl_vm_parm_attr =
	__ATTR(parm, S_IRUGO, ipl_vm_parm_show, शून्य);

अटल sमाप_प्रकार sys_ipl_device_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	चयन (ipl_info.type) अणु
	हाल IPL_TYPE_CCW:
		वापस प्र_लिखो(page, "0.%x.%04x\n", ipl_block.ccw.ssid,
			       ipl_block.ccw.devno);
	हाल IPL_TYPE_FCP:
	हाल IPL_TYPE_FCP_DUMP:
		वापस प्र_लिखो(page, "0.0.%04x\n", ipl_block.fcp.devno);
	हाल IPL_TYPE_NVME:
	हाल IPL_TYPE_NVME_DUMP:
		वापस प्र_लिखो(page, "%08ux\n", ipl_block.nvme.fid);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा kobj_attribute sys_ipl_device_attr =
	__ATTR(device, S_IRUGO, sys_ipl_device_show, शून्य);

अटल sमाप_प्रकार ipl_parameter_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *attr, अक्षर *buf,
				  loff_t off, माप_प्रकार count)
अणु
	वापस memory_पढ़ो_from_buffer(buf, count, &off, &ipl_block,
				       ipl_block.hdr.len);
पूर्ण
अटल काष्ठा bin_attribute ipl_parameter_attr =
	__BIN_ATTR(binary_parameter, S_IRUGO, ipl_parameter_पढ़ो, शून्य,
		   PAGE_SIZE);

अटल sमाप_प्रकार ipl_scp_data_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *attr, अक्षर *buf,
				 loff_t off, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक size = ipl_block.fcp.scp_data_len;
	व्योम *scp_data = &ipl_block.fcp.scp_data;

	वापस memory_पढ़ो_from_buffer(buf, count, &off, scp_data, size);
पूर्ण

अटल sमाप_प्रकार ipl_nvme_scp_data_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *attr, अक्षर *buf,
				 loff_t off, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक size = ipl_block.nvme.scp_data_len;
	व्योम *scp_data = &ipl_block.nvme.scp_data;

	वापस memory_पढ़ो_from_buffer(buf, count, &off, scp_data, size);
पूर्ण

अटल काष्ठा bin_attribute ipl_scp_data_attr =
	__BIN_ATTR(scp_data, S_IRUGO, ipl_scp_data_पढ़ो, शून्य, PAGE_SIZE);

अटल काष्ठा bin_attribute ipl_nvme_scp_data_attr =
	__BIN_ATTR(scp_data, S_IRUGO, ipl_nvme_scp_data_पढ़ो, शून्य, PAGE_SIZE);

अटल काष्ठा bin_attribute *ipl_fcp_bin_attrs[] = अणु
	&ipl_parameter_attr,
	&ipl_scp_data_attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *ipl_nvme_bin_attrs[] = अणु
	&ipl_parameter_attr,
	&ipl_nvme_scp_data_attr,
	शून्य,
पूर्ण;

/* FCP ipl device attributes */

DEFINE_IPL_ATTR_RO(ipl_fcp, wwpn, "0x%016llx\n",
		   (अचिन्हित दीर्घ दीर्घ)ipl_block.fcp.wwpn);
DEFINE_IPL_ATTR_RO(ipl_fcp, lun, "0x%016llx\n",
		   (अचिन्हित दीर्घ दीर्घ)ipl_block.fcp.lun);
DEFINE_IPL_ATTR_RO(ipl_fcp, bootprog, "%lld\n",
		   (अचिन्हित दीर्घ दीर्घ)ipl_block.fcp.bootprog);
DEFINE_IPL_ATTR_RO(ipl_fcp, br_lba, "%lld\n",
		   (अचिन्हित दीर्घ दीर्घ)ipl_block.fcp.br_lba);

/* NVMe ipl device attributes */
DEFINE_IPL_ATTR_RO(ipl_nvme, fid, "0x%08llx\n",
		   (अचिन्हित दीर्घ दीर्घ)ipl_block.nvme.fid);
DEFINE_IPL_ATTR_RO(ipl_nvme, nsid, "0x%08llx\n",
		   (अचिन्हित दीर्घ दीर्घ)ipl_block.nvme.nsid);
DEFINE_IPL_ATTR_RO(ipl_nvme, bootprog, "%lld\n",
		   (अचिन्हित दीर्घ दीर्घ)ipl_block.nvme.bootprog);
DEFINE_IPL_ATTR_RO(ipl_nvme, br_lba, "%lld\n",
		   (अचिन्हित दीर्घ दीर्घ)ipl_block.nvme.br_lba);

अटल sमाप_प्रकार ipl_ccw_loadparm_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	अक्षर loadparm[LOADPARM_LEN + 1] = अणुपूर्ण;

	अगर (!sclp_ipl_info.is_valid)
		वापस प्र_लिखो(page, "#unknown#\n");
	स_नकल(loadparm, &sclp_ipl_info.loadparm, LOADPARM_LEN);
	EBCASC(loadparm, LOADPARM_LEN);
	strim(loadparm);
	वापस प्र_लिखो(page, "%s\n", loadparm);
पूर्ण

अटल काष्ठा kobj_attribute sys_ipl_ccw_loadparm_attr =
	__ATTR(loadparm, 0444, ipl_ccw_loadparm_show, शून्य);

अटल काष्ठा attribute *ipl_fcp_attrs[] = अणु
	&sys_ipl_type_attr.attr,
	&sys_ipl_device_attr.attr,
	&sys_ipl_fcp_wwpn_attr.attr,
	&sys_ipl_fcp_lun_attr.attr,
	&sys_ipl_fcp_bootprog_attr.attr,
	&sys_ipl_fcp_br_lba_attr.attr,
	&sys_ipl_ccw_loadparm_attr.attr,
	&sys_ipl_secure_attr.attr,
	&sys_ipl_has_secure_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group ipl_fcp_attr_group = अणु
	.attrs = ipl_fcp_attrs,
	.bin_attrs = ipl_fcp_bin_attrs,
पूर्ण;

अटल काष्ठा attribute *ipl_nvme_attrs[] = अणु
	&sys_ipl_type_attr.attr,
	&sys_ipl_nvme_fid_attr.attr,
	&sys_ipl_nvme_nsid_attr.attr,
	&sys_ipl_nvme_bootprog_attr.attr,
	&sys_ipl_nvme_br_lba_attr.attr,
	&sys_ipl_ccw_loadparm_attr.attr,
	&sys_ipl_secure_attr.attr,
	&sys_ipl_has_secure_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group ipl_nvme_attr_group = अणु
	.attrs = ipl_nvme_attrs,
	.bin_attrs = ipl_nvme_bin_attrs,
पूर्ण;


/* CCW ipl device attributes */

अटल काष्ठा attribute *ipl_ccw_attrs_vm[] = अणु
	&sys_ipl_type_attr.attr,
	&sys_ipl_device_attr.attr,
	&sys_ipl_ccw_loadparm_attr.attr,
	&sys_ipl_vm_parm_attr.attr,
	&sys_ipl_secure_attr.attr,
	&sys_ipl_has_secure_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ipl_ccw_attrs_lpar[] = अणु
	&sys_ipl_type_attr.attr,
	&sys_ipl_device_attr.attr,
	&sys_ipl_ccw_loadparm_attr.attr,
	&sys_ipl_secure_attr.attr,
	&sys_ipl_has_secure_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group ipl_ccw_attr_group_vm = अणु
	.attrs = ipl_ccw_attrs_vm,
पूर्ण;

अटल काष्ठा attribute_group ipl_ccw_attr_group_lpar = अणु
	.attrs = ipl_ccw_attrs_lpar
पूर्ण;

/* UNKNOWN ipl device attributes */

अटल काष्ठा attribute *ipl_unknown_attrs[] = अणु
	&sys_ipl_type_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group ipl_unknown_attr_group = अणु
	.attrs = ipl_unknown_attrs,
पूर्ण;

अटल काष्ठा kset *ipl_kset;

अटल व्योम __ipl_run(व्योम *unused)
अणु
	__bpon();
	diag308(DIAG308_LOAD_CLEAR, शून्य);
पूर्ण

अटल व्योम ipl_run(काष्ठा shutकरोwn_trigger *trigger)
अणु
	smp_call_ipl_cpu(__ipl_run, शून्य);
पूर्ण

अटल पूर्णांक __init ipl_init(व्योम)
अणु
	पूर्णांक rc;

	ipl_kset = kset_create_and_add("ipl", शून्य, firmware_kobj);
	अगर (!ipl_kset) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	चयन (ipl_info.type) अणु
	हाल IPL_TYPE_CCW:
		अगर (MACHINE_IS_VM)
			rc = sysfs_create_group(&ipl_kset->kobj,
						&ipl_ccw_attr_group_vm);
		अन्यथा
			rc = sysfs_create_group(&ipl_kset->kobj,
						&ipl_ccw_attr_group_lpar);
		अवरोध;
	हाल IPL_TYPE_FCP:
	हाल IPL_TYPE_FCP_DUMP:
		rc = sysfs_create_group(&ipl_kset->kobj, &ipl_fcp_attr_group);
		अवरोध;
	हाल IPL_TYPE_NVME:
	हाल IPL_TYPE_NVME_DUMP:
		rc = sysfs_create_group(&ipl_kset->kobj, &ipl_nvme_attr_group);
		अवरोध;
	शेष:
		rc = sysfs_create_group(&ipl_kset->kobj,
					&ipl_unknown_attr_group);
		अवरोध;
	पूर्ण
out:
	अगर (rc)
		panic("ipl_init failed: rc = %i\n", rc);

	वापस 0;
पूर्ण

अटल काष्ठा shutकरोwn_action __refdata ipl_action = अणु
	.name	= SHUTDOWN_ACTION_IPL_STR,
	.fn	= ipl_run,
	.init	= ipl_init,
पूर्ण;

/*
 * reipl shutकरोwn action: Reboot Linux on shutकरोwn.
 */

/* VM IPL PARM attributes */
अटल sमाप_प्रकार reipl_generic_vmparm_show(काष्ठा ipl_parameter_block *ipb,
					  अक्षर *page)
अणु
	अक्षर vmparm[DIAG308_VMPARM_SIZE + 1] = अणुपूर्ण;

	ipl_block_get_ascii_vmparm(vmparm, माप(vmparm), ipb);
	वापस प्र_लिखो(page, "%s\n", vmparm);
पूर्ण

अटल sमाप_प्रकार reipl_generic_vmparm_store(काष्ठा ipl_parameter_block *ipb,
					  माप_प्रकार vmparm_max,
					  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक i, ip_len;

	/* ignore trailing newline */
	ip_len = len;
	अगर ((len > 0) && (buf[len - 1] == '\n'))
		ip_len--;

	अगर (ip_len > vmparm_max)
		वापस -EINVAL;

	/* parm is used to store kernel options, check क्रम common अक्षरs */
	क्रम (i = 0; i < ip_len; i++)
		अगर (!(है_अक्षर_अंक(buf[i]) || isascii(buf[i]) || है_छाप(buf[i])))
			वापस -EINVAL;

	स_रखो(ipb->ccw.vm_parm, 0, DIAG308_VMPARM_SIZE);
	ipb->ccw.vm_parm_len = ip_len;
	अगर (ip_len > 0) अणु
		ipb->ccw.vm_flags |= IPL_PB0_CCW_VM_FLAG_VP;
		स_नकल(ipb->ccw.vm_parm, buf, ip_len);
		ASCEBC(ipb->ccw.vm_parm, ip_len);
	पूर्ण अन्यथा अणु
		ipb->ccw.vm_flags &= ~IPL_PB0_CCW_VM_FLAG_VP;
	पूर्ण

	वापस len;
पूर्ण

/* NSS wrapper */
अटल sमाप_प्रकार reipl_nss_vmparm_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस reipl_generic_vmparm_show(reipl_block_nss, page);
पूर्ण

अटल sमाप_प्रकार reipl_nss_vmparm_store(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस reipl_generic_vmparm_store(reipl_block_nss, 56, buf, len);
पूर्ण

/* CCW wrapper */
अटल sमाप_प्रकार reipl_ccw_vmparm_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस reipl_generic_vmparm_show(reipl_block_ccw, page);
पूर्ण

अटल sमाप_प्रकार reipl_ccw_vmparm_store(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस reipl_generic_vmparm_store(reipl_block_ccw, 64, buf, len);
पूर्ण

अटल काष्ठा kobj_attribute sys_reipl_nss_vmparm_attr =
	__ATTR(parm, S_IRUGO | S_IWUSR, reipl_nss_vmparm_show,
					reipl_nss_vmparm_store);
अटल काष्ठा kobj_attribute sys_reipl_ccw_vmparm_attr =
	__ATTR(parm, S_IRUGO | S_IWUSR, reipl_ccw_vmparm_show,
					reipl_ccw_vmparm_store);

/* FCP reipl device attributes */

अटल sमाप_प्रकार reipl_fcp_scpdata_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				      काष्ठा bin_attribute *attr,
				      अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	माप_प्रकार size = reipl_block_fcp->fcp.scp_data_len;
	व्योम *scp_data = reipl_block_fcp->fcp.scp_data;

	वापस memory_पढ़ो_from_buffer(buf, count, &off, scp_data, size);
पूर्ण

अटल sमाप_प्रकार reipl_fcp_scpdata_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				       काष्ठा bin_attribute *attr,
				       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	माप_प्रकार scpdata_len = count;
	माप_प्रकार padding;


	अगर (off)
		वापस -EINVAL;

	स_नकल(reipl_block_fcp->fcp.scp_data, buf, count);
	अगर (scpdata_len % 8) अणु
		padding = 8 - (scpdata_len % 8);
		स_रखो(reipl_block_fcp->fcp.scp_data + scpdata_len,
		       0, padding);
		scpdata_len += padding;
	पूर्ण

	reipl_block_fcp->hdr.len = IPL_BP_FCP_LEN + scpdata_len;
	reipl_block_fcp->fcp.len = IPL_BP0_FCP_LEN + scpdata_len;
	reipl_block_fcp->fcp.scp_data_len = scpdata_len;

	वापस count;
पूर्ण
अटल काष्ठा bin_attribute sys_reipl_fcp_scp_data_attr =
	__BIN_ATTR(scp_data, (S_IRUGO | S_IWUSR), reipl_fcp_scpdata_पढ़ो,
		   reipl_fcp_scpdata_ग_लिखो, DIAG308_SCPDATA_SIZE);

अटल काष्ठा bin_attribute *reipl_fcp_bin_attrs[] = अणु
	&sys_reipl_fcp_scp_data_attr,
	शून्य,
पूर्ण;

DEFINE_IPL_ATTR_RW(reipl_fcp, wwpn, "0x%016llx\n", "%llx\n",
		   reipl_block_fcp->fcp.wwpn);
DEFINE_IPL_ATTR_RW(reipl_fcp, lun, "0x%016llx\n", "%llx\n",
		   reipl_block_fcp->fcp.lun);
DEFINE_IPL_ATTR_RW(reipl_fcp, bootprog, "%lld\n", "%lld\n",
		   reipl_block_fcp->fcp.bootprog);
DEFINE_IPL_ATTR_RW(reipl_fcp, br_lba, "%lld\n", "%lld\n",
		   reipl_block_fcp->fcp.br_lba);
DEFINE_IPL_ATTR_RW(reipl_fcp, device, "0.0.%04llx\n", "0.0.%llx\n",
		   reipl_block_fcp->fcp.devno);

अटल व्योम reipl_get_ascii_loadparm(अक्षर *loadparm,
				     काष्ठा ipl_parameter_block *ibp)
अणु
	स_नकल(loadparm, ibp->common.loadparm, LOADPARM_LEN);
	EBCASC(loadparm, LOADPARM_LEN);
	loadparm[LOADPARM_LEN] = 0;
	strim(loadparm);
पूर्ण

अटल sमाप_प्रकार reipl_generic_loadparm_show(काष्ठा ipl_parameter_block *ipb,
					   अक्षर *page)
अणु
	अक्षर buf[LOADPARM_LEN + 1];

	reipl_get_ascii_loadparm(buf, ipb);
	वापस प्र_लिखो(page, "%s\n", buf);
पूर्ण

अटल sमाप_प्रकार reipl_generic_loadparm_store(काष्ठा ipl_parameter_block *ipb,
					    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक i, lp_len;

	/* ignore trailing newline */
	lp_len = len;
	अगर ((len > 0) && (buf[len - 1] == '\n'))
		lp_len--;
	/* loadparm can have max 8 अक्षरacters and must not start with a blank */
	अगर ((lp_len > LOADPARM_LEN) || ((lp_len > 0) && (buf[0] == ' ')))
		वापस -EINVAL;
	/* loadparm can only contain "a-z,A-Z,0-9,SP,." */
	क्रम (i = 0; i < lp_len; i++) अणु
		अगर (है_अक्षर(buf[i]) || है_अंक(buf[i]) || (buf[i] == ' ') ||
		    (buf[i] == '.'))
			जारी;
		वापस -EINVAL;
	पूर्ण
	/* initialize loadparm with blanks */
	स_रखो(ipb->common.loadparm, ' ', LOADPARM_LEN);
	/* copy and convert to ebcdic */
	स_नकल(ipb->common.loadparm, buf, lp_len);
	ASCEBC(ipb->common.loadparm, LOADPARM_LEN);
	ipb->common.flags |= IPL_PB0_FLAG_LOADPARM;
	वापस len;
पूर्ण

/* FCP wrapper */
अटल sमाप_प्रकार reipl_fcp_loadparm_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस reipl_generic_loadparm_show(reipl_block_fcp, page);
पूर्ण

अटल sमाप_प्रकार reipl_fcp_loadparm_store(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस reipl_generic_loadparm_store(reipl_block_fcp, buf, len);
पूर्ण

अटल काष्ठा kobj_attribute sys_reipl_fcp_loadparm_attr =
	__ATTR(loadparm, S_IRUGO | S_IWUSR, reipl_fcp_loadparm_show,
					    reipl_fcp_loadparm_store);

अटल sमाप_प्रकार reipl_fcp_clear_show(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", reipl_fcp_clear);
पूर्ण

अटल sमाप_प्रकार reipl_fcp_clear_store(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (strtobool(buf, &reipl_fcp_clear) < 0)
		वापस -EINVAL;
	वापस len;
पूर्ण

अटल काष्ठा attribute *reipl_fcp_attrs[] = अणु
	&sys_reipl_fcp_device_attr.attr,
	&sys_reipl_fcp_wwpn_attr.attr,
	&sys_reipl_fcp_lun_attr.attr,
	&sys_reipl_fcp_bootprog_attr.attr,
	&sys_reipl_fcp_br_lba_attr.attr,
	&sys_reipl_fcp_loadparm_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group reipl_fcp_attr_group = अणु
	.attrs = reipl_fcp_attrs,
	.bin_attrs = reipl_fcp_bin_attrs,
पूर्ण;

अटल काष्ठा kobj_attribute sys_reipl_fcp_clear_attr =
	__ATTR(clear, 0644, reipl_fcp_clear_show, reipl_fcp_clear_store);

/* NVME reipl device attributes */

अटल sमाप_प्रकार reipl_nvme_scpdata_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				      काष्ठा bin_attribute *attr,
				      अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	माप_प्रकार size = reipl_block_nvme->nvme.scp_data_len;
	व्योम *scp_data = reipl_block_nvme->nvme.scp_data;

	वापस memory_पढ़ो_from_buffer(buf, count, &off, scp_data, size);
पूर्ण

अटल sमाप_प्रकार reipl_nvme_scpdata_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				       काष्ठा bin_attribute *attr,
				       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	माप_प्रकार scpdata_len = count;
	माप_प्रकार padding;

	अगर (off)
		वापस -EINVAL;

	स_नकल(reipl_block_nvme->nvme.scp_data, buf, count);
	अगर (scpdata_len % 8) अणु
		padding = 8 - (scpdata_len % 8);
		स_रखो(reipl_block_nvme->nvme.scp_data + scpdata_len,
		       0, padding);
		scpdata_len += padding;
	पूर्ण

	reipl_block_nvme->hdr.len = IPL_BP_FCP_LEN + scpdata_len;
	reipl_block_nvme->nvme.len = IPL_BP0_FCP_LEN + scpdata_len;
	reipl_block_nvme->nvme.scp_data_len = scpdata_len;

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sys_reipl_nvme_scp_data_attr =
	__BIN_ATTR(scp_data, (S_IRUGO | S_IWUSR), reipl_nvme_scpdata_पढ़ो,
		   reipl_nvme_scpdata_ग_लिखो, DIAG308_SCPDATA_SIZE);

अटल काष्ठा bin_attribute *reipl_nvme_bin_attrs[] = अणु
	&sys_reipl_nvme_scp_data_attr,
	शून्य,
पूर्ण;

DEFINE_IPL_ATTR_RW(reipl_nvme, fid, "0x%08llx\n", "%llx\n",
		   reipl_block_nvme->nvme.fid);
DEFINE_IPL_ATTR_RW(reipl_nvme, nsid, "0x%08llx\n", "%llx\n",
		   reipl_block_nvme->nvme.nsid);
DEFINE_IPL_ATTR_RW(reipl_nvme, bootprog, "%lld\n", "%lld\n",
		   reipl_block_nvme->nvme.bootprog);
DEFINE_IPL_ATTR_RW(reipl_nvme, br_lba, "%lld\n", "%lld\n",
		   reipl_block_nvme->nvme.br_lba);

/* nvme wrapper */
अटल sमाप_प्रकार reipl_nvme_loadparm_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस reipl_generic_loadparm_show(reipl_block_nvme, page);
पूर्ण

अटल sमाप_प्रकार reipl_nvme_loadparm_store(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस reipl_generic_loadparm_store(reipl_block_nvme, buf, len);
पूर्ण

अटल काष्ठा kobj_attribute sys_reipl_nvme_loadparm_attr =
	__ATTR(loadparm, S_IRUGO | S_IWUSR, reipl_nvme_loadparm_show,
					    reipl_nvme_loadparm_store);

अटल काष्ठा attribute *reipl_nvme_attrs[] = अणु
	&sys_reipl_nvme_fid_attr.attr,
	&sys_reipl_nvme_nsid_attr.attr,
	&sys_reipl_nvme_bootprog_attr.attr,
	&sys_reipl_nvme_br_lba_attr.attr,
	&sys_reipl_nvme_loadparm_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group reipl_nvme_attr_group = अणु
	.attrs = reipl_nvme_attrs,
	.bin_attrs = reipl_nvme_bin_attrs
पूर्ण;

अटल sमाप_प्रकार reipl_nvme_clear_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", reipl_nvme_clear);
पूर्ण

अटल sमाप_प्रकार reipl_nvme_clear_store(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (strtobool(buf, &reipl_nvme_clear) < 0)
		वापस -EINVAL;
	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute sys_reipl_nvme_clear_attr =
	__ATTR(clear, 0644, reipl_nvme_clear_show, reipl_nvme_clear_store);

/* CCW reipl device attributes */
DEFINE_IPL_CCW_ATTR_RW(reipl_ccw, device, reipl_block_ccw->ccw);

/* NSS wrapper */
अटल sमाप_प्रकार reipl_nss_loadparm_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस reipl_generic_loadparm_show(reipl_block_nss, page);
पूर्ण

अटल sमाप_प्रकार reipl_nss_loadparm_store(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस reipl_generic_loadparm_store(reipl_block_nss, buf, len);
पूर्ण

/* CCW wrapper */
अटल sमाप_प्रकार reipl_ccw_loadparm_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस reipl_generic_loadparm_show(reipl_block_ccw, page);
पूर्ण

अटल sमाप_प्रकार reipl_ccw_loadparm_store(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस reipl_generic_loadparm_store(reipl_block_ccw, buf, len);
पूर्ण

अटल काष्ठा kobj_attribute sys_reipl_ccw_loadparm_attr =
	__ATTR(loadparm, S_IRUGO | S_IWUSR, reipl_ccw_loadparm_show,
					    reipl_ccw_loadparm_store);

अटल sमाप_प्रकार reipl_ccw_clear_show(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", reipl_ccw_clear);
पूर्ण

अटल sमाप_प्रकार reipl_ccw_clear_store(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (strtobool(buf, &reipl_ccw_clear) < 0)
		वापस -EINVAL;
	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute sys_reipl_ccw_clear_attr =
	__ATTR(clear, 0644, reipl_ccw_clear_show, reipl_ccw_clear_store);

अटल काष्ठा attribute *reipl_ccw_attrs_vm[] = अणु
	&sys_reipl_ccw_device_attr.attr,
	&sys_reipl_ccw_loadparm_attr.attr,
	&sys_reipl_ccw_vmparm_attr.attr,
	&sys_reipl_ccw_clear_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *reipl_ccw_attrs_lpar[] = अणु
	&sys_reipl_ccw_device_attr.attr,
	&sys_reipl_ccw_loadparm_attr.attr,
	&sys_reipl_ccw_clear_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group reipl_ccw_attr_group_vm = अणु
	.name  = IPL_CCW_STR,
	.attrs = reipl_ccw_attrs_vm,
पूर्ण;

अटल काष्ठा attribute_group reipl_ccw_attr_group_lpar = अणु
	.name  = IPL_CCW_STR,
	.attrs = reipl_ccw_attrs_lpar,
पूर्ण;


/* NSS reipl device attributes */
अटल व्योम reipl_get_ascii_nss_name(अक्षर *dst,
				     काष्ठा ipl_parameter_block *ipb)
अणु
	स_नकल(dst, ipb->ccw.nss_name, NSS_NAME_SIZE);
	EBCASC(dst, NSS_NAME_SIZE);
	dst[NSS_NAME_SIZE] = 0;
पूर्ण

अटल sमाप_प्रकार reipl_nss_name_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	अक्षर nss_name[NSS_NAME_SIZE + 1] = अणुपूर्ण;

	reipl_get_ascii_nss_name(nss_name, reipl_block_nss);
	वापस प्र_लिखो(page, "%s\n", nss_name);
पूर्ण

अटल sमाप_प्रकार reipl_nss_name_store(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक nss_len;

	/* ignore trailing newline */
	nss_len = len;
	अगर ((len > 0) && (buf[len - 1] == '\n'))
		nss_len--;

	अगर (nss_len > NSS_NAME_SIZE)
		वापस -EINVAL;

	स_रखो(reipl_block_nss->ccw.nss_name, 0x40, NSS_NAME_SIZE);
	अगर (nss_len > 0) अणु
		reipl_block_nss->ccw.vm_flags |= IPL_PB0_CCW_VM_FLAG_NSS;
		स_नकल(reipl_block_nss->ccw.nss_name, buf, nss_len);
		ASCEBC(reipl_block_nss->ccw.nss_name, nss_len);
		EBC_TOUPPER(reipl_block_nss->ccw.nss_name, nss_len);
	पूर्ण अन्यथा अणु
		reipl_block_nss->ccw.vm_flags &= ~IPL_PB0_CCW_VM_FLAG_NSS;
	पूर्ण

	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute sys_reipl_nss_name_attr =
	__ATTR(name, S_IRUGO | S_IWUSR, reipl_nss_name_show,
					reipl_nss_name_store);

अटल काष्ठा kobj_attribute sys_reipl_nss_loadparm_attr =
	__ATTR(loadparm, S_IRUGO | S_IWUSR, reipl_nss_loadparm_show,
					    reipl_nss_loadparm_store);

अटल काष्ठा attribute *reipl_nss_attrs[] = अणु
	&sys_reipl_nss_name_attr.attr,
	&sys_reipl_nss_loadparm_attr.attr,
	&sys_reipl_nss_vmparm_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group reipl_nss_attr_group = अणु
	.name  = IPL_NSS_STR,
	.attrs = reipl_nss_attrs,
पूर्ण;

व्योम set_os_info_reipl_block(व्योम)
अणु
	os_info_entry_add(OS_INFO_REIPL_BLOCK, reipl_block_actual,
			  reipl_block_actual->hdr.len);
पूर्ण

/* reipl type */

अटल पूर्णांक reipl_set_type(क्रमागत ipl_type type)
अणु
	अगर (!(reipl_capabilities & type))
		वापस -EINVAL;

	चयन(type) अणु
	हाल IPL_TYPE_CCW:
		reipl_block_actual = reipl_block_ccw;
		अवरोध;
	हाल IPL_TYPE_FCP:
		reipl_block_actual = reipl_block_fcp;
		अवरोध;
	हाल IPL_TYPE_NVME:
		reipl_block_actual = reipl_block_nvme;
		अवरोध;
	हाल IPL_TYPE_NSS:
		reipl_block_actual = reipl_block_nss;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	reipl_type = type;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार reipl_type_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", ipl_type_str(reipl_type));
पूर्ण

अटल sमाप_प्रकार reipl_type_store(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक rc = -EINVAL;

	अगर (म_भेदन(buf, IPL_CCW_STR, म_माप(IPL_CCW_STR)) == 0)
		rc = reipl_set_type(IPL_TYPE_CCW);
	अन्यथा अगर (म_भेदन(buf, IPL_FCP_STR, म_माप(IPL_FCP_STR)) == 0)
		rc = reipl_set_type(IPL_TYPE_FCP);
	अन्यथा अगर (म_भेदन(buf, IPL_NVME_STR, म_माप(IPL_NVME_STR)) == 0)
		rc = reipl_set_type(IPL_TYPE_NVME);
	अन्यथा अगर (म_भेदन(buf, IPL_NSS_STR, म_माप(IPL_NSS_STR)) == 0)
		rc = reipl_set_type(IPL_TYPE_NSS);
	वापस (rc != 0) ? rc : len;
पूर्ण

अटल काष्ठा kobj_attribute reipl_type_attr =
	__ATTR(reipl_type, 0644, reipl_type_show, reipl_type_store);

अटल काष्ठा kset *reipl_kset;
अटल काष्ठा kset *reipl_fcp_kset;
अटल काष्ठा kset *reipl_nvme_kset;

अटल व्योम __reipl_run(व्योम *unused)
अणु
	चयन (reipl_type) अणु
	हाल IPL_TYPE_CCW:
		diag308(DIAG308_SET, reipl_block_ccw);
		अगर (reipl_ccw_clear)
			diag308(DIAG308_LOAD_CLEAR, शून्य);
		अन्यथा
			diag308(DIAG308_LOAD_NORMAL_DUMP, शून्य);
		अवरोध;
	हाल IPL_TYPE_FCP:
		diag308(DIAG308_SET, reipl_block_fcp);
		अगर (reipl_fcp_clear)
			diag308(DIAG308_LOAD_CLEAR, शून्य);
		अन्यथा
			diag308(DIAG308_LOAD_NORMAL, शून्य);
		अवरोध;
	हाल IPL_TYPE_NVME:
		diag308(DIAG308_SET, reipl_block_nvme);
		अगर (reipl_nvme_clear)
			diag308(DIAG308_LOAD_CLEAR, शून्य);
		अन्यथा
			diag308(DIAG308_LOAD_NORMAL, शून्य);
		अवरोध;
	हाल IPL_TYPE_NSS:
		diag308(DIAG308_SET, reipl_block_nss);
		diag308(DIAG308_LOAD_CLEAR, शून्य);
		अवरोध;
	हाल IPL_TYPE_UNKNOWN:
		diag308(DIAG308_LOAD_CLEAR, शून्य);
		अवरोध;
	हाल IPL_TYPE_FCP_DUMP:
	हाल IPL_TYPE_NVME_DUMP:
		अवरोध;
	पूर्ण
	disabled_रुको();
पूर्ण

अटल व्योम reipl_run(काष्ठा shutकरोwn_trigger *trigger)
अणु
	smp_call_ipl_cpu(__reipl_run, शून्य);
पूर्ण

अटल व्योम reipl_block_ccw_init(काष्ठा ipl_parameter_block *ipb)
अणु
	ipb->hdr.len = IPL_BP_CCW_LEN;
	ipb->hdr.version = IPL_PARM_BLOCK_VERSION;
	ipb->pb0_hdr.len = IPL_BP0_CCW_LEN;
	ipb->pb0_hdr.pbt = IPL_PBT_CCW;
पूर्ण

अटल व्योम reipl_block_ccw_fill_parms(काष्ठा ipl_parameter_block *ipb)
अणु
	/* LOADPARM */
	/* check अगर पढ़ो scp info worked and set loadparm */
	अगर (sclp_ipl_info.is_valid)
		स_नकल(ipb->ccw.loadparm, &sclp_ipl_info.loadparm, LOADPARM_LEN);
	अन्यथा
		/* पढ़ो scp info failed: set empty loadparm (EBCDIC blanks) */
		स_रखो(ipb->ccw.loadparm, 0x40, LOADPARM_LEN);
	ipb->ccw.flags = IPL_PB0_FLAG_LOADPARM;

	/* VM PARM */
	अगर (MACHINE_IS_VM && ipl_block_valid &&
	    (ipl_block.ccw.vm_flags & IPL_PB0_CCW_VM_FLAG_VP)) अणु

		ipb->ccw.vm_flags |= IPL_PB0_CCW_VM_FLAG_VP;
		ipb->ccw.vm_parm_len = ipl_block.ccw.vm_parm_len;
		स_नकल(ipb->ccw.vm_parm,
		       ipl_block.ccw.vm_parm, DIAG308_VMPARM_SIZE);
	पूर्ण
पूर्ण

अटल पूर्णांक __init reipl_nss_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!MACHINE_IS_VM)
		वापस 0;

	reipl_block_nss = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!reipl_block_nss)
		वापस -ENOMEM;

	rc = sysfs_create_group(&reipl_kset->kobj, &reipl_nss_attr_group);
	अगर (rc)
		वापस rc;

	reipl_block_ccw_init(reipl_block_nss);
	reipl_capabilities |= IPL_TYPE_NSS;
	वापस 0;
पूर्ण

अटल पूर्णांक __init reipl_ccw_init(व्योम)
अणु
	पूर्णांक rc;

	reipl_block_ccw = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!reipl_block_ccw)
		वापस -ENOMEM;

	rc = sysfs_create_group(&reipl_kset->kobj,
				MACHINE_IS_VM ? &reipl_ccw_attr_group_vm
					      : &reipl_ccw_attr_group_lpar);
	अगर (rc)
		वापस rc;

	reipl_block_ccw_init(reipl_block_ccw);
	अगर (ipl_info.type == IPL_TYPE_CCW) अणु
		reipl_block_ccw->ccw.ssid = ipl_block.ccw.ssid;
		reipl_block_ccw->ccw.devno = ipl_block.ccw.devno;
		reipl_block_ccw_fill_parms(reipl_block_ccw);
	पूर्ण

	reipl_capabilities |= IPL_TYPE_CCW;
	वापस 0;
पूर्ण

अटल पूर्णांक __init reipl_fcp_init(व्योम)
अणु
	पूर्णांक rc;

	reipl_block_fcp = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!reipl_block_fcp)
		वापस -ENOMEM;

	/* sysfs: create fcp kset क्रम mixing attr group and bin attrs */
	reipl_fcp_kset = kset_create_and_add(IPL_FCP_STR, शून्य,
					     &reipl_kset->kobj);
	अगर (!reipl_fcp_kset) अणु
		मुक्त_page((अचिन्हित दीर्घ) reipl_block_fcp);
		वापस -ENOMEM;
	पूर्ण

	rc = sysfs_create_group(&reipl_fcp_kset->kobj, &reipl_fcp_attr_group);
	अगर (rc)
		जाओ out1;

	अगर (test_facility(141)) अणु
		rc = sysfs_create_file(&reipl_fcp_kset->kobj,
				       &sys_reipl_fcp_clear_attr.attr);
		अगर (rc)
			जाओ out2;
	पूर्ण अन्यथा अणु
		reipl_fcp_clear = true;
	पूर्ण

	अगर (ipl_info.type == IPL_TYPE_FCP) अणु
		स_नकल(reipl_block_fcp, &ipl_block, माप(ipl_block));
		/*
		 * Fix loadparm: There are प्रणालीs where the (SCSI) LOADPARM
		 * is invalid in the SCSI IPL parameter block, so take it
		 * always from sclp_ipl_info.
		 */
		स_नकल(reipl_block_fcp->fcp.loadparm, sclp_ipl_info.loadparm,
		       LOADPARM_LEN);
	पूर्ण अन्यथा अणु
		reipl_block_fcp->hdr.len = IPL_BP_FCP_LEN;
		reipl_block_fcp->hdr.version = IPL_PARM_BLOCK_VERSION;
		reipl_block_fcp->fcp.len = IPL_BP0_FCP_LEN;
		reipl_block_fcp->fcp.pbt = IPL_PBT_FCP;
		reipl_block_fcp->fcp.opt = IPL_PB0_FCP_OPT_IPL;
	पूर्ण
	reipl_capabilities |= IPL_TYPE_FCP;
	वापस 0;

out2:
	sysfs_हटाओ_group(&reipl_fcp_kset->kobj, &reipl_fcp_attr_group);
out1:
	kset_unरेजिस्टर(reipl_fcp_kset);
	मुक्त_page((अचिन्हित दीर्घ) reipl_block_fcp);
	वापस rc;
पूर्ण

अटल पूर्णांक __init reipl_nvme_init(व्योम)
अणु
	पूर्णांक rc;

	reipl_block_nvme = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!reipl_block_nvme)
		वापस -ENOMEM;

	/* sysfs: create kset क्रम mixing attr group and bin attrs */
	reipl_nvme_kset = kset_create_and_add(IPL_NVME_STR, शून्य,
					     &reipl_kset->kobj);
	अगर (!reipl_nvme_kset) अणु
		मुक्त_page((अचिन्हित दीर्घ) reipl_block_nvme);
		वापस -ENOMEM;
	पूर्ण

	rc = sysfs_create_group(&reipl_nvme_kset->kobj, &reipl_nvme_attr_group);
	अगर (rc)
		जाओ out1;

	अगर (test_facility(141)) अणु
		rc = sysfs_create_file(&reipl_nvme_kset->kobj,
				       &sys_reipl_nvme_clear_attr.attr);
		अगर (rc)
			जाओ out2;
	पूर्ण अन्यथा अणु
		reipl_nvme_clear = true;
	पूर्ण

	अगर (ipl_info.type == IPL_TYPE_NVME) अणु
		स_नकल(reipl_block_nvme, &ipl_block, माप(ipl_block));
		/*
		 * Fix loadparm: There are प्रणालीs where the (SCSI) LOADPARM
		 * is invalid in the IPL parameter block, so take it
		 * always from sclp_ipl_info.
		 */
		स_नकल(reipl_block_nvme->nvme.loadparm, sclp_ipl_info.loadparm,
		       LOADPARM_LEN);
	पूर्ण अन्यथा अणु
		reipl_block_nvme->hdr.len = IPL_BP_NVME_LEN;
		reipl_block_nvme->hdr.version = IPL_PARM_BLOCK_VERSION;
		reipl_block_nvme->nvme.len = IPL_BP0_NVME_LEN;
		reipl_block_nvme->nvme.pbt = IPL_PBT_NVME;
		reipl_block_nvme->nvme.opt = IPL_PB0_NVME_OPT_IPL;
	पूर्ण
	reipl_capabilities |= IPL_TYPE_NVME;
	वापस 0;

out2:
	sysfs_हटाओ_group(&reipl_nvme_kset->kobj, &reipl_nvme_attr_group);
out1:
	kset_unरेजिस्टर(reipl_nvme_kset);
	मुक्त_page((अचिन्हित दीर्घ) reipl_block_nvme);
	वापस rc;
पूर्ण

अटल पूर्णांक __init reipl_type_init(व्योम)
अणु
	क्रमागत ipl_type reipl_type = ipl_info.type;
	काष्ठा ipl_parameter_block *reipl_block;
	अचिन्हित दीर्घ size;

	reipl_block = os_info_old_entry(OS_INFO_REIPL_BLOCK, &size);
	अगर (!reipl_block)
		जाओ out;
	/*
	 * If we have an OS info reipl block, this will be used
	 */
	अगर (reipl_block->pb0_hdr.pbt == IPL_PBT_FCP) अणु
		स_नकल(reipl_block_fcp, reipl_block, size);
		reipl_type = IPL_TYPE_FCP;
	पूर्ण अन्यथा अगर (reipl_block->pb0_hdr.pbt == IPL_PBT_NVME) अणु
		स_नकल(reipl_block_nvme, reipl_block, size);
		reipl_type = IPL_TYPE_NVME;
	पूर्ण अन्यथा अगर (reipl_block->pb0_hdr.pbt == IPL_PBT_CCW) अणु
		स_नकल(reipl_block_ccw, reipl_block, size);
		reipl_type = IPL_TYPE_CCW;
	पूर्ण
out:
	वापस reipl_set_type(reipl_type);
पूर्ण

अटल पूर्णांक __init reipl_init(व्योम)
अणु
	पूर्णांक rc;

	reipl_kset = kset_create_and_add("reipl", शून्य, firmware_kobj);
	अगर (!reipl_kset)
		वापस -ENOMEM;
	rc = sysfs_create_file(&reipl_kset->kobj, &reipl_type_attr.attr);
	अगर (rc) अणु
		kset_unरेजिस्टर(reipl_kset);
		वापस rc;
	पूर्ण
	rc = reipl_ccw_init();
	अगर (rc)
		वापस rc;
	rc = reipl_fcp_init();
	अगर (rc)
		वापस rc;
	rc = reipl_nvme_init();
	अगर (rc)
		वापस rc;
	rc = reipl_nss_init();
	अगर (rc)
		वापस rc;
	वापस reipl_type_init();
पूर्ण

अटल काष्ठा shutकरोwn_action __refdata reipl_action = अणु
	.name	= SHUTDOWN_ACTION_REIPL_STR,
	.fn	= reipl_run,
	.init	= reipl_init,
पूर्ण;

/*
 * dump shutकरोwn action: Dump Linux on shutकरोwn.
 */

/* FCP dump device attributes */

DEFINE_IPL_ATTR_RW(dump_fcp, wwpn, "0x%016llx\n", "%llx\n",
		   dump_block_fcp->fcp.wwpn);
DEFINE_IPL_ATTR_RW(dump_fcp, lun, "0x%016llx\n", "%llx\n",
		   dump_block_fcp->fcp.lun);
DEFINE_IPL_ATTR_RW(dump_fcp, bootprog, "%lld\n", "%lld\n",
		   dump_block_fcp->fcp.bootprog);
DEFINE_IPL_ATTR_RW(dump_fcp, br_lba, "%lld\n", "%lld\n",
		   dump_block_fcp->fcp.br_lba);
DEFINE_IPL_ATTR_RW(dump_fcp, device, "0.0.%04llx\n", "0.0.%llx\n",
		   dump_block_fcp->fcp.devno);

अटल काष्ठा attribute *dump_fcp_attrs[] = अणु
	&sys_dump_fcp_device_attr.attr,
	&sys_dump_fcp_wwpn_attr.attr,
	&sys_dump_fcp_lun_attr.attr,
	&sys_dump_fcp_bootprog_attr.attr,
	&sys_dump_fcp_br_lba_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group dump_fcp_attr_group = अणु
	.name  = IPL_FCP_STR,
	.attrs = dump_fcp_attrs,
पूर्ण;

/* NVME dump device attributes */
DEFINE_IPL_ATTR_RW(dump_nvme, fid, "0x%08llx\n", "%llx\n",
		   dump_block_nvme->nvme.fid);
DEFINE_IPL_ATTR_RW(dump_nvme, nsid, "0x%08llx\n", "%llx\n",
		   dump_block_nvme->nvme.nsid);
DEFINE_IPL_ATTR_RW(dump_nvme, bootprog, "%lld\n", "%llx\n",
		   dump_block_nvme->nvme.bootprog);
DEFINE_IPL_ATTR_RW(dump_nvme, br_lba, "%lld\n", "%llx\n",
		   dump_block_nvme->nvme.br_lba);

अटल काष्ठा attribute *dump_nvme_attrs[] = अणु
	&sys_dump_nvme_fid_attr.attr,
	&sys_dump_nvme_nsid_attr.attr,
	&sys_dump_nvme_bootprog_attr.attr,
	&sys_dump_nvme_br_lba_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group dump_nvme_attr_group = अणु
	.name  = IPL_NVME_STR,
	.attrs = dump_nvme_attrs,
पूर्ण;

/* CCW dump device attributes */
DEFINE_IPL_CCW_ATTR_RW(dump_ccw, device, dump_block_ccw->ccw);

अटल काष्ठा attribute *dump_ccw_attrs[] = अणु
	&sys_dump_ccw_device_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group dump_ccw_attr_group = अणु
	.name  = IPL_CCW_STR,
	.attrs = dump_ccw_attrs,
पूर्ण;

/* dump type */

अटल पूर्णांक dump_set_type(क्रमागत dump_type type)
अणु
	अगर (!(dump_capabilities & type))
		वापस -EINVAL;
	dump_type = type;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार dump_type_show(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", dump_type_str(dump_type));
पूर्ण

अटल sमाप_प्रकार dump_type_store(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक rc = -EINVAL;

	अगर (म_भेदन(buf, DUMP_NONE_STR, म_माप(DUMP_NONE_STR)) == 0)
		rc = dump_set_type(DUMP_TYPE_NONE);
	अन्यथा अगर (म_भेदन(buf, DUMP_CCW_STR, म_माप(DUMP_CCW_STR)) == 0)
		rc = dump_set_type(DUMP_TYPE_CCW);
	अन्यथा अगर (म_भेदन(buf, DUMP_FCP_STR, म_माप(DUMP_FCP_STR)) == 0)
		rc = dump_set_type(DUMP_TYPE_FCP);
	अन्यथा अगर (म_भेदन(buf, DUMP_NVME_STR, म_माप(DUMP_NVME_STR)) == 0)
		rc = dump_set_type(DUMP_TYPE_NVME);
	वापस (rc != 0) ? rc : len;
पूर्ण

अटल काष्ठा kobj_attribute dump_type_attr =
	__ATTR(dump_type, 0644, dump_type_show, dump_type_store);

अटल काष्ठा kset *dump_kset;

अटल व्योम diag308_dump(व्योम *dump_block)
अणु
	diag308(DIAG308_SET, dump_block);
	जबतक (1) अणु
		अगर (diag308(DIAG308_LOAD_NORMAL_DUMP, शून्य) != 0x302)
			अवरोध;
		udelay(USEC_PER_SEC);
	पूर्ण
पूर्ण

अटल व्योम __dump_run(व्योम *unused)
अणु
	चयन (dump_type) अणु
	हाल DUMP_TYPE_CCW:
		diag308_dump(dump_block_ccw);
		अवरोध;
	हाल DUMP_TYPE_FCP:
		diag308_dump(dump_block_fcp);
		अवरोध;
	हाल DUMP_TYPE_NVME:
		diag308_dump(dump_block_nvme);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dump_run(काष्ठा shutकरोwn_trigger *trigger)
अणु
	अगर (dump_type == DUMP_TYPE_NONE)
		वापस;
	smp_send_stop();
	smp_call_ipl_cpu(__dump_run, शून्य);
पूर्ण

अटल पूर्णांक __init dump_ccw_init(व्योम)
अणु
	पूर्णांक rc;

	dump_block_ccw = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!dump_block_ccw)
		वापस -ENOMEM;
	rc = sysfs_create_group(&dump_kset->kobj, &dump_ccw_attr_group);
	अगर (rc) अणु
		मुक्त_page((अचिन्हित दीर्घ)dump_block_ccw);
		वापस rc;
	पूर्ण
	dump_block_ccw->hdr.len = IPL_BP_CCW_LEN;
	dump_block_ccw->hdr.version = IPL_PARM_BLOCK_VERSION;
	dump_block_ccw->ccw.len = IPL_BP0_CCW_LEN;
	dump_block_ccw->ccw.pbt = IPL_PBT_CCW;
	dump_capabilities |= DUMP_TYPE_CCW;
	वापस 0;
पूर्ण

अटल पूर्णांक __init dump_fcp_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!sclp_ipl_info.has_dump)
		वापस 0; /* LDIPL DUMP is not installed */
	dump_block_fcp = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!dump_block_fcp)
		वापस -ENOMEM;
	rc = sysfs_create_group(&dump_kset->kobj, &dump_fcp_attr_group);
	अगर (rc) अणु
		मुक्त_page((अचिन्हित दीर्घ)dump_block_fcp);
		वापस rc;
	पूर्ण
	dump_block_fcp->hdr.len = IPL_BP_FCP_LEN;
	dump_block_fcp->hdr.version = IPL_PARM_BLOCK_VERSION;
	dump_block_fcp->fcp.len = IPL_BP0_FCP_LEN;
	dump_block_fcp->fcp.pbt = IPL_PBT_FCP;
	dump_block_fcp->fcp.opt = IPL_PB0_FCP_OPT_DUMP;
	dump_capabilities |= DUMP_TYPE_FCP;
	वापस 0;
पूर्ण

अटल पूर्णांक __init dump_nvme_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!sclp_ipl_info.has_dump)
		वापस 0; /* LDIPL DUMP is not installed */
	dump_block_nvme = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!dump_block_nvme)
		वापस -ENOMEM;
	rc = sysfs_create_group(&dump_kset->kobj, &dump_nvme_attr_group);
	अगर (rc) अणु
		मुक्त_page((अचिन्हित दीर्घ)dump_block_nvme);
		वापस rc;
	पूर्ण
	dump_block_nvme->hdr.len = IPL_BP_NVME_LEN;
	dump_block_nvme->hdr.version = IPL_PARM_BLOCK_VERSION;
	dump_block_nvme->fcp.len = IPL_BP0_NVME_LEN;
	dump_block_nvme->fcp.pbt = IPL_PBT_NVME;
	dump_block_nvme->fcp.opt = IPL_PB0_NVME_OPT_DUMP;
	dump_capabilities |= DUMP_TYPE_NVME;
	वापस 0;
पूर्ण

अटल पूर्णांक __init dump_init(व्योम)
अणु
	पूर्णांक rc;

	dump_kset = kset_create_and_add("dump", शून्य, firmware_kobj);
	अगर (!dump_kset)
		वापस -ENOMEM;
	rc = sysfs_create_file(&dump_kset->kobj, &dump_type_attr.attr);
	अगर (rc) अणु
		kset_unरेजिस्टर(dump_kset);
		वापस rc;
	पूर्ण
	rc = dump_ccw_init();
	अगर (rc)
		वापस rc;
	rc = dump_fcp_init();
	अगर (rc)
		वापस rc;
	rc = dump_nvme_init();
	अगर (rc)
		वापस rc;
	dump_set_type(DUMP_TYPE_NONE);
	वापस 0;
पूर्ण

अटल काष्ठा shutकरोwn_action __refdata dump_action = अणु
	.name	= SHUTDOWN_ACTION_DUMP_STR,
	.fn	= dump_run,
	.init	= dump_init,
पूर्ण;

अटल व्योम dump_reipl_run(काष्ठा shutकरोwn_trigger *trigger)
अणु
	अचिन्हित दीर्घ ipib = (अचिन्हित दीर्घ) reipl_block_actual;
	अचिन्हित पूर्णांक csum;

	csum = (__क्रमce अचिन्हित पूर्णांक)
	       csum_partial(reipl_block_actual, reipl_block_actual->hdr.len, 0);
	mem_assign_असलolute(S390_lowcore.ipib, ipib);
	mem_assign_असलolute(S390_lowcore.ipib_checksum, csum);
	dump_run(trigger);
पूर्ण

अटल काष्ठा shutकरोwn_action __refdata dump_reipl_action = अणु
	.name	= SHUTDOWN_ACTION_DUMP_REIPL_STR,
	.fn	= dump_reipl_run,
पूर्ण;

/*
 * vmcmd shutकरोwn action: Trigger vm command on shutकरोwn.
 */

अटल अक्षर vmcmd_on_reboot[128];
अटल अक्षर vmcmd_on_panic[128];
अटल अक्षर vmcmd_on_halt[128];
अटल अक्षर vmcmd_on_poff[128];
अटल अक्षर vmcmd_on_restart[128];

DEFINE_IPL_ATTR_STR_RW(vmcmd, on_reboot, "%s\n", "%s\n", vmcmd_on_reboot);
DEFINE_IPL_ATTR_STR_RW(vmcmd, on_panic, "%s\n", "%s\n", vmcmd_on_panic);
DEFINE_IPL_ATTR_STR_RW(vmcmd, on_halt, "%s\n", "%s\n", vmcmd_on_halt);
DEFINE_IPL_ATTR_STR_RW(vmcmd, on_poff, "%s\n", "%s\n", vmcmd_on_poff);
DEFINE_IPL_ATTR_STR_RW(vmcmd, on_restart, "%s\n", "%s\n", vmcmd_on_restart);

अटल काष्ठा attribute *vmcmd_attrs[] = अणु
	&sys_vmcmd_on_reboot_attr.attr,
	&sys_vmcmd_on_panic_attr.attr,
	&sys_vmcmd_on_halt_attr.attr,
	&sys_vmcmd_on_poff_attr.attr,
	&sys_vmcmd_on_restart_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group vmcmd_attr_group = अणु
	.attrs = vmcmd_attrs,
पूर्ण;

अटल काष्ठा kset *vmcmd_kset;

अटल व्योम vmcmd_run(काष्ठा shutकरोwn_trigger *trigger)
अणु
	अक्षर *cmd;

	अगर (म_भेद(trigger->name, ON_REIPL_STR) == 0)
		cmd = vmcmd_on_reboot;
	अन्यथा अगर (म_भेद(trigger->name, ON_PANIC_STR) == 0)
		cmd = vmcmd_on_panic;
	अन्यथा अगर (म_भेद(trigger->name, ON_HALT_STR) == 0)
		cmd = vmcmd_on_halt;
	अन्यथा अगर (म_भेद(trigger->name, ON_POFF_STR) == 0)
		cmd = vmcmd_on_poff;
	अन्यथा अगर (म_भेद(trigger->name, ON_RESTART_STR) == 0)
		cmd = vmcmd_on_restart;
	अन्यथा
		वापस;

	अगर (म_माप(cmd) == 0)
		वापस;
	__cpcmd(cmd, शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक vmcmd_init(व्योम)
अणु
	अगर (!MACHINE_IS_VM)
		वापस -EOPNOTSUPP;
	vmcmd_kset = kset_create_and_add("vmcmd", शून्य, firmware_kobj);
	अगर (!vmcmd_kset)
		वापस -ENOMEM;
	वापस sysfs_create_group(&vmcmd_kset->kobj, &vmcmd_attr_group);
पूर्ण

अटल काष्ठा shutकरोwn_action vmcmd_action = अणुSHUTDOWN_ACTION_VMCMD_STR,
					      vmcmd_run, vmcmd_initपूर्ण;

/*
 * stop shutकरोwn action: Stop Linux on shutकरोwn.
 */

अटल व्योम stop_run(काष्ठा shutकरोwn_trigger *trigger)
अणु
	अगर (म_भेद(trigger->name, ON_PANIC_STR) == 0 ||
	    म_भेद(trigger->name, ON_RESTART_STR) == 0)
		disabled_रुको();
	smp_stop_cpu();
पूर्ण

अटल काष्ठा shutकरोwn_action stop_action = अणुSHUTDOWN_ACTION_STOP_STR,
					     stop_run, शून्यपूर्ण;

/* action list */

अटल काष्ठा shutकरोwn_action *shutकरोwn_actions_list[] = अणु
	&ipl_action, &reipl_action, &dump_reipl_action, &dump_action,
	&vmcmd_action, &stop_actionपूर्ण;
#घोषणा SHUTDOWN_ACTIONS_COUNT (माप(shutकरोwn_actions_list) / माप(व्योम *))

/*
 * Trigger section
 */

अटल काष्ठा kset *shutकरोwn_actions_kset;

अटल पूर्णांक set_trigger(स्थिर अक्षर *buf, काष्ठा shutकरोwn_trigger *trigger,
		       माप_प्रकार len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SHUTDOWN_ACTIONS_COUNT; i++) अणु
		अगर (sysfs_streq(buf, shutकरोwn_actions_list[i]->name)) अणु
			अगर (shutकरोwn_actions_list[i]->init_rc) अणु
				वापस shutकरोwn_actions_list[i]->init_rc;
			पूर्ण अन्यथा अणु
				trigger->action = shutकरोwn_actions_list[i];
				वापस len;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* on reipl */

अटल काष्ठा shutकरोwn_trigger on_reboot_trigger = अणुON_REIPL_STR,
						    &reipl_actionपूर्ण;

अटल sमाप_प्रकार on_reboot_show(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", on_reboot_trigger.action->name);
पूर्ण

अटल sमाप_प्रकार on_reboot_store(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस set_trigger(buf, &on_reboot_trigger, len);
पूर्ण
अटल काष्ठा kobj_attribute on_reboot_attr = __ATTR_RW(on_reboot);

अटल व्योम करो_machine_restart(अक्षर *__unused)
अणु
	smp_send_stop();
	on_reboot_trigger.action->fn(&on_reboot_trigger);
	reipl_run(शून्य);
पूर्ण
व्योम (*_machine_restart)(अक्षर *command) = करो_machine_restart;

/* on panic */

अटल काष्ठा shutकरोwn_trigger on_panic_trigger = अणुON_PANIC_STR, &stop_actionपूर्ण;

अटल sमाप_प्रकार on_panic_show(काष्ठा kobject *kobj,
			     काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", on_panic_trigger.action->name);
पूर्ण

अटल sमाप_प्रकार on_panic_store(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस set_trigger(buf, &on_panic_trigger, len);
पूर्ण
अटल काष्ठा kobj_attribute on_panic_attr = __ATTR_RW(on_panic);

अटल व्योम करो_panic(व्योम)
अणु
	lgr_info_log();
	on_panic_trigger.action->fn(&on_panic_trigger);
	stop_run(&on_panic_trigger);
पूर्ण

/* on restart */

अटल काष्ठा shutकरोwn_trigger on_restart_trigger = अणुON_RESTART_STR,
	&stop_actionपूर्ण;

अटल sमाप_प्रकार on_restart_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", on_restart_trigger.action->name);
पूर्ण

अटल sमाप_प्रकार on_restart_store(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस set_trigger(buf, &on_restart_trigger, len);
पूर्ण
अटल काष्ठा kobj_attribute on_restart_attr = __ATTR_RW(on_restart);

अटल व्योम __करो_restart(व्योम *ignore)
अणु
	__arch_local_irq_stosm(0x04); /* enable DAT */
	smp_send_stop();
#अगर_घोषित CONFIG_CRASH_DUMP
	crash_kexec(शून्य);
#पूर्ण_अगर
	on_restart_trigger.action->fn(&on_restart_trigger);
	stop_run(&on_restart_trigger);
पूर्ण

व्योम करो_restart(व्योम *arg)
अणु
	tracing_off();
	debug_locks_off();
	lgr_info_log();
	smp_call_online_cpu(__करो_restart, arg);
पूर्ण

/* on halt */

अटल काष्ठा shutकरोwn_trigger on_halt_trigger = अणुON_HALT_STR, &stop_actionपूर्ण;

अटल sमाप_प्रकार on_halt_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", on_halt_trigger.action->name);
पूर्ण

अटल sमाप_प्रकार on_halt_store(काष्ठा kobject *kobj,
			     काष्ठा kobj_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस set_trigger(buf, &on_halt_trigger, len);
पूर्ण
अटल काष्ठा kobj_attribute on_halt_attr = __ATTR_RW(on_halt);

अटल व्योम करो_machine_halt(व्योम)
अणु
	smp_send_stop();
	on_halt_trigger.action->fn(&on_halt_trigger);
	stop_run(&on_halt_trigger);
पूर्ण
व्योम (*_machine_halt)(व्योम) = करो_machine_halt;

/* on घातer off */

अटल काष्ठा shutकरोwn_trigger on_poff_trigger = अणुON_POFF_STR, &stop_actionपूर्ण;

अटल sमाप_प्रकार on_poff_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", on_poff_trigger.action->name);
पूर्ण

अटल sमाप_प्रकार on_poff_store(काष्ठा kobject *kobj,
			     काष्ठा kobj_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस set_trigger(buf, &on_poff_trigger, len);
पूर्ण
अटल काष्ठा kobj_attribute on_poff_attr = __ATTR_RW(on_poff);

अटल व्योम करो_machine_घातer_off(व्योम)
अणु
	smp_send_stop();
	on_poff_trigger.action->fn(&on_poff_trigger);
	stop_run(&on_poff_trigger);
पूर्ण
व्योम (*_machine_घातer_off)(व्योम) = करो_machine_घातer_off;

अटल काष्ठा attribute *shutकरोwn_action_attrs[] = अणु
	&on_restart_attr.attr,
	&on_reboot_attr.attr,
	&on_panic_attr.attr,
	&on_halt_attr.attr,
	&on_poff_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group shutकरोwn_action_attr_group = अणु
	.attrs = shutकरोwn_action_attrs,
पूर्ण;

अटल व्योम __init shutकरोwn_triggers_init(व्योम)
अणु
	shutकरोwn_actions_kset = kset_create_and_add("shutdown_actions", शून्य,
						    firmware_kobj);
	अगर (!shutकरोwn_actions_kset)
		जाओ fail;
	अगर (sysfs_create_group(&shutकरोwn_actions_kset->kobj,
			       &shutकरोwn_action_attr_group))
		जाओ fail;
	वापस;
fail:
	panic("shutdown_triggers_init failed\n");
पूर्ण

अटल व्योम __init shutकरोwn_actions_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SHUTDOWN_ACTIONS_COUNT; i++) अणु
		अगर (!shutकरोwn_actions_list[i]->init)
			जारी;
		shutकरोwn_actions_list[i]->init_rc =
			shutकरोwn_actions_list[i]->init();
	पूर्ण
पूर्ण

अटल पूर्णांक __init s390_ipl_init(व्योम)
अणु
	अक्षर str[8] = अणु0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40पूर्ण;

	sclp_early_get_ipl_info(&sclp_ipl_info);
	/*
	 * Fix loadparm: There are प्रणालीs where the (SCSI) LOADPARM
	 * वापसed by पढ़ो SCP info is invalid (contains EBCDIC blanks)
	 * when the प्रणाली has been booted via diag308. In that हाल we use
	 * the value from diag308, अगर available.
	 *
	 * There are also प्रणालीs where diag308 store करोes not work in
	 * हाल the प्रणाली is booted from HMC. Fortunately in this हाल
	 * READ SCP info provides the correct value.
	 */
	अगर (स_भेद(sclp_ipl_info.loadparm, str, माप(str)) == 0 && ipl_block_valid)
		स_नकल(sclp_ipl_info.loadparm, ipl_block.ccw.loadparm, LOADPARM_LEN);
	shutकरोwn_actions_init();
	shutकरोwn_triggers_init();
	वापस 0;
पूर्ण

__initcall(s390_ipl_init);

अटल व्योम __init म_नकलन_skip_quote(अक्षर *dst, अक्षर *src, पूर्णांक n)
अणु
	पूर्णांक sx, dx;

	dx = 0;
	क्रम (sx = 0; src[sx] != 0; sx++) अणु
		अगर (src[sx] == '"')
			जारी;
		dst[dx++] = src[sx];
		अगर (dx >= n)
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __init vmcmd_on_reboot_setup(अक्षर *str)
अणु
	अगर (!MACHINE_IS_VM)
		वापस 1;
	म_नकलन_skip_quote(vmcmd_on_reboot, str, 127);
	vmcmd_on_reboot[127] = 0;
	on_reboot_trigger.action = &vmcmd_action;
	वापस 1;
पूर्ण
__setup("vmreboot=", vmcmd_on_reboot_setup);

अटल पूर्णांक __init vmcmd_on_panic_setup(अक्षर *str)
अणु
	अगर (!MACHINE_IS_VM)
		वापस 1;
	म_नकलन_skip_quote(vmcmd_on_panic, str, 127);
	vmcmd_on_panic[127] = 0;
	on_panic_trigger.action = &vmcmd_action;
	वापस 1;
पूर्ण
__setup("vmpanic=", vmcmd_on_panic_setup);

अटल पूर्णांक __init vmcmd_on_halt_setup(अक्षर *str)
अणु
	अगर (!MACHINE_IS_VM)
		वापस 1;
	म_नकलन_skip_quote(vmcmd_on_halt, str, 127);
	vmcmd_on_halt[127] = 0;
	on_halt_trigger.action = &vmcmd_action;
	वापस 1;
पूर्ण
__setup("vmhalt=", vmcmd_on_halt_setup);

अटल पूर्णांक __init vmcmd_on_poff_setup(अक्षर *str)
अणु
	अगर (!MACHINE_IS_VM)
		वापस 1;
	म_नकलन_skip_quote(vmcmd_on_poff, str, 127);
	vmcmd_on_poff[127] = 0;
	on_poff_trigger.action = &vmcmd_action;
	वापस 1;
पूर्ण
__setup("vmpoff=", vmcmd_on_poff_setup);

अटल पूर्णांक on_panic_notअगरy(काष्ठा notअगरier_block *self,
			   अचिन्हित दीर्घ event, व्योम *data)
अणु
	करो_panic();
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block on_panic_nb = अणु
	.notअगरier_call = on_panic_notअगरy,
	.priority = पूर्णांक_न्यून,
पूर्ण;

व्योम __init setup_ipl(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा ipl_parameter_block) != PAGE_SIZE);

	ipl_info.type = get_ipl_type();
	चयन (ipl_info.type) अणु
	हाल IPL_TYPE_CCW:
		ipl_info.data.ccw.dev_id.ssid = ipl_block.ccw.ssid;
		ipl_info.data.ccw.dev_id.devno = ipl_block.ccw.devno;
		अवरोध;
	हाल IPL_TYPE_FCP:
	हाल IPL_TYPE_FCP_DUMP:
		ipl_info.data.fcp.dev_id.ssid = 0;
		ipl_info.data.fcp.dev_id.devno = ipl_block.fcp.devno;
		ipl_info.data.fcp.wwpn = ipl_block.fcp.wwpn;
		ipl_info.data.fcp.lun = ipl_block.fcp.lun;
		अवरोध;
	हाल IPL_TYPE_NVME:
	हाल IPL_TYPE_NVME_DUMP:
		ipl_info.data.nvme.fid = ipl_block.nvme.fid;
		ipl_info.data.nvme.nsid = ipl_block.nvme.nsid;
		अवरोध;
	हाल IPL_TYPE_NSS:
	हाल IPL_TYPE_UNKNOWN:
		/* We have no info to copy */
		अवरोध;
	पूर्ण
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &on_panic_nb);
पूर्ण

व्योम s390_reset_प्रणाली(व्योम)
अणु
	/* Disable prefixing */
	set_prefix(0);

	/* Disable lowcore protection */
	__ctl_clear_bit(0, 28);
	diag_dma_ops.diag308_reset();
पूर्ण

#अगर_घोषित CONFIG_KEXEC_खाता

पूर्णांक ipl_report_add_component(काष्ठा ipl_report *report, काष्ठा kexec_buf *kbuf,
			     अचिन्हित अक्षर flags, अचिन्हित लघु cert)
अणु
	काष्ठा ipl_report_component *comp;

	comp = vzalloc(माप(*comp));
	अगर (!comp)
		वापस -ENOMEM;
	list_add_tail(&comp->list, &report->components);

	comp->entry.addr = kbuf->mem;
	comp->entry.len = kbuf->memsz;
	comp->entry.flags = flags;
	comp->entry.certअगरicate_index = cert;

	report->size += माप(comp->entry);

	वापस 0;
पूर्ण

पूर्णांक ipl_report_add_certअगरicate(काष्ठा ipl_report *report, व्योम *key,
			       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	काष्ठा ipl_report_certअगरicate *cert;

	cert = vzalloc(माप(*cert));
	अगर (!cert)
		वापस -ENOMEM;
	list_add_tail(&cert->list, &report->certअगरicates);

	cert->entry.addr = addr;
	cert->entry.len = len;
	cert->key = key;

	report->size += माप(cert->entry);
	report->size += cert->entry.len;

	वापस 0;
पूर्ण

काष्ठा ipl_report *ipl_report_init(काष्ठा ipl_parameter_block *ipib)
अणु
	काष्ठा ipl_report *report;

	report = vzalloc(माप(*report));
	अगर (!report)
		वापस ERR_PTR(-ENOMEM);

	report->ipib = ipib;
	INIT_LIST_HEAD(&report->components);
	INIT_LIST_HEAD(&report->certअगरicates);

	report->size = ALIGN(ipib->hdr.len, 8);
	report->size += माप(काष्ठा ipl_rl_hdr);
	report->size += माप(काष्ठा ipl_rb_components);
	report->size += माप(काष्ठा ipl_rb_certअगरicates);

	वापस report;
पूर्ण

व्योम *ipl_report_finish(काष्ठा ipl_report *report)
अणु
	काष्ठा ipl_report_certअगरicate *cert;
	काष्ठा ipl_report_component *comp;
	काष्ठा ipl_rb_certअगरicates *certs;
	काष्ठा ipl_parameter_block *ipib;
	काष्ठा ipl_rb_components *comps;
	काष्ठा ipl_rl_hdr *rl_hdr;
	व्योम *buf, *ptr;

	buf = vzalloc(report->size);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);
	ptr = buf;

	स_नकल(ptr, report->ipib, report->ipib->hdr.len);
	ipib = ptr;
	अगर (ipl_secure_flag)
		ipib->hdr.flags |= IPL_PL_FLAG_SIPL;
	ipib->hdr.flags |= IPL_PL_FLAG_IPLSR;
	ptr += report->ipib->hdr.len;
	ptr = PTR_ALIGN(ptr, 8);

	rl_hdr = ptr;
	ptr += माप(*rl_hdr);

	comps = ptr;
	comps->rbt = IPL_RBT_COMPONENTS;
	ptr += माप(*comps);
	list_क्रम_each_entry(comp, &report->components, list) अणु
		स_नकल(ptr, &comp->entry, माप(comp->entry));
		ptr += माप(comp->entry);
	पूर्ण
	comps->len = ptr - (व्योम *)comps;

	certs = ptr;
	certs->rbt = IPL_RBT_CERTIFICATES;
	ptr += माप(*certs);
	list_क्रम_each_entry(cert, &report->certअगरicates, list) अणु
		स_नकल(ptr, &cert->entry, माप(cert->entry));
		ptr += माप(cert->entry);
	पूर्ण
	certs->len = ptr - (व्योम *)certs;
	rl_hdr->len = ptr - (व्योम *)rl_hdr;

	list_क्रम_each_entry(cert, &report->certअगरicates, list) अणु
		स_नकल(ptr, cert->key, cert->entry.len);
		ptr += cert->entry.len;
	पूर्ण

	BUG_ON(ptr > buf + report->size);
	वापस buf;
पूर्ण

पूर्णांक ipl_report_मुक्त(काष्ठा ipl_report *report)
अणु
	काष्ठा ipl_report_component *comp, *ncomp;
	काष्ठा ipl_report_certअगरicate *cert, *ncert;

	list_क्रम_each_entry_safe(comp, ncomp, &report->components, list)
		vमुक्त(comp);

	list_क्रम_each_entry_safe(cert, ncert, &report->certअगरicates, list)
		vमुक्त(cert);

	vमुक्त(report);

	वापस 0;
पूर्ण

#पूर्ण_अगर
