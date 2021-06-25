<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause
/*
 * Copyright (C) 2020 VMware, Inc., Palo Alto, CA., USA
 *
 * PTP घड़ी driver क्रम VMware precision घड़ी भव device.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/vmware.h>

#घोषणा VMWARE_MAGIC 0x564D5868
#घोषणा VMWARE_CMD_PCLK(nr) ((nr << 16) | 97)
#घोषणा VMWARE_CMD_PCLK_GETTIME VMWARE_CMD_PCLK(0)

अटल काष्ठा acpi_device *ptp_vmw_acpi_device;
अटल काष्ठा ptp_घड़ी *ptp_vmw_घड़ी;


अटल पूर्णांक ptp_vmw_pclk_पढ़ो(u64 *ns)
अणु
	u32 ret, nsec_hi, nsec_lo, unused1, unused2, unused3;

	यंत्र अस्थिर (VMWARE_HYPERCALL :
		"=a"(ret), "=b"(nsec_hi), "=c"(nsec_lo), "=d"(unused1),
		"=S"(unused2), "=D"(unused3) :
		"a"(VMWARE_MAGIC), "b"(0),
		"c"(VMWARE_CMD_PCLK_GETTIME), "d"(0) :
		"memory");

	अगर (ret == 0)
		*ns = ((u64)nsec_hi << 32) | nsec_lo;
	वापस ret;
पूर्ण

/*
 * PTP घड़ी ops.
 */

अटल पूर्णांक ptp_vmw_adjसमय(काष्ठा ptp_घड़ी_info *info, s64 delta)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ptp_vmw_adjfreq(काष्ठा ptp_घड़ी_info *info, s32 delta)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ptp_vmw_समय_लो(काष्ठा ptp_घड़ी_info *info, काष्ठा बारpec64 *ts)
अणु
	u64 ns;

	अगर (ptp_vmw_pclk_पढ़ो(&ns) != 0)
		वापस -EIO;
	*ts = ns_to_बारpec64(ns);
	वापस 0;
पूर्ण

अटल पूर्णांक ptp_vmw_समय_रखो(काष्ठा ptp_घड़ी_info *info,
			  स्थिर काष्ठा बारpec64 *ts)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ptp_vmw_enable(काष्ठा ptp_घड़ी_info *info,
			 काष्ठा ptp_घड़ी_request *request, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल काष्ठा ptp_घड़ी_info ptp_vmw_घड़ी_info = अणु
	.owner		= THIS_MODULE,
	.name		= "ptp_vmw",
	.max_adj	= 0,
	.adjसमय	= ptp_vmw_adjसमय,
	.adjfreq	= ptp_vmw_adjfreq,
	.समय_लो64	= ptp_vmw_समय_लो,
	.समय_रखो64	= ptp_vmw_समय_रखो,
	.enable		= ptp_vmw_enable,
पूर्ण;

/*
 * ACPI driver ops क्रम VMware "precision clock" भव device.
 */

अटल पूर्णांक ptp_vmw_acpi_add(काष्ठा acpi_device *device)
अणु
	ptp_vmw_घड़ी = ptp_घड़ी_रेजिस्टर(&ptp_vmw_घड़ी_info, शून्य);
	अगर (IS_ERR(ptp_vmw_घड़ी)) अणु
		pr_err("failed to register ptp clock\n");
		वापस PTR_ERR(ptp_vmw_घड़ी);
	पूर्ण

	ptp_vmw_acpi_device = device;
	वापस 0;
पूर्ण

अटल पूर्णांक ptp_vmw_acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	ptp_घड़ी_unरेजिस्टर(ptp_vmw_घड़ी);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ptp_vmw_acpi_device_ids[] = अणु
	अणु "VMW0005", 0 पूर्ण,
	अणु "", 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, ptp_vmw_acpi_device_ids);

अटल काष्ठा acpi_driver ptp_vmw_acpi_driver = अणु
	.name = "ptp_vmw",
	.ids = ptp_vmw_acpi_device_ids,
	.ops = अणु
		.add = ptp_vmw_acpi_add,
		.हटाओ	= ptp_vmw_acpi_हटाओ
	पूर्ण,
	.owner	= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init ptp_vmw_init(व्योम)
अणु
	अगर (x86_hyper_type != X86_HYPER_VMWARE)
		वापस -1;
	वापस acpi_bus_रेजिस्टर_driver(&ptp_vmw_acpi_driver);
पूर्ण

अटल व्योम __निकास ptp_vmw_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&ptp_vmw_acpi_driver);
पूर्ण

module_init(ptp_vmw_init);
module_निकास(ptp_vmw_निकास);

MODULE_DESCRIPTION("VMware virtual PTP clock driver");
MODULE_AUTHOR("VMware, Inc.");
MODULE_LICENSE("Dual BSD/GPL");
