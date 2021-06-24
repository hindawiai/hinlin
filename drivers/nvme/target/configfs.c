<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Configfs पूर्णांकerface क्रम the NVMe target.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/pci.h>
#समावेश <linux/pci-p2pdma.h>

#समावेश "nvmet.h"

अटल स्थिर काष्ठा config_item_type nvmet_host_type;
अटल स्थिर काष्ठा config_item_type nvmet_subsys_type;

अटल LIST_HEAD(nvmet_ports_list);
काष्ठा list_head *nvmet_ports = &nvmet_ports_list;

काष्ठा nvmet_type_name_map अणु
	u8		type;
	स्थिर अक्षर	*name;
पूर्ण;

अटल काष्ठा nvmet_type_name_map nvmet_transport[] = अणु
	अणु NVMF_TRTYPE_RDMA,	"rdma" पूर्ण,
	अणु NVMF_TRTYPE_FC,	"fc" पूर्ण,
	अणु NVMF_TRTYPE_TCP,	"tcp" पूर्ण,
	अणु NVMF_TRTYPE_LOOP,	"loop" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvmet_type_name_map nvmet_addr_family[] = अणु
	अणु NVMF_ADDR_FAMILY_PCI,		"pcie" पूर्ण,
	अणु NVMF_ADDR_FAMILY_IP4,		"ipv4" पूर्ण,
	अणु NVMF_ADDR_FAMILY_IP6,		"ipv6" पूर्ण,
	अणु NVMF_ADDR_FAMILY_IB,		"ib" पूर्ण,
	अणु NVMF_ADDR_FAMILY_FC,		"fc" पूर्ण,
	अणु NVMF_ADDR_FAMILY_LOOP,	"loop" पूर्ण,
पूर्ण;

अटल bool nvmet_is_port_enabled(काष्ठा nvmet_port *p, स्थिर अक्षर *caller)
अणु
	अगर (p->enabled)
		pr_err("Disable port '%u' before changing attribute in %s\n",
		       le16_to_cpu(p->disc_addr.portid), caller);
	वापस p->enabled;
पूर्ण

/*
 * nvmet_port Generic ConfigFS definitions.
 * Used in any place in the ConfigFS tree that refers to an address.
 */
अटल sमाप_प्रकार nvmet_addr_adrfam_show(काष्ठा config_item *item, अक्षर *page)
अणु
	u8 adrfam = to_nvmet_port(item)->disc_addr.adrfam;
	पूर्णांक i;

	क्रम (i = 1; i < ARRAY_SIZE(nvmet_addr_family); i++) अणु
		अगर (nvmet_addr_family[i].type == adrfam)
			वापस प्र_लिखो(page, "%s\n", nvmet_addr_family[i].name);
	पूर्ण

	वापस प्र_लिखो(page, "\n");
पूर्ण

अटल sमाप_प्रकार nvmet_addr_adrfam_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);
	पूर्णांक i;

	अगर (nvmet_is_port_enabled(port, __func__))
		वापस -EACCES;

	क्रम (i = 1; i < ARRAY_SIZE(nvmet_addr_family); i++) अणु
		अगर (sysfs_streq(page, nvmet_addr_family[i].name))
			जाओ found;
	पूर्ण

	pr_err("Invalid value '%s' for adrfam\n", page);
	वापस -EINVAL;

found:
	port->disc_addr.adrfam = nvmet_addr_family[i].type;
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_, addr_adrfam);

अटल sमाप_प्रकार nvmet_addr_portid_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%d\n",
			le16_to_cpu(port->disc_addr.portid));
पूर्ण

अटल sमाप_प्रकार nvmet_addr_portid_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);
	u16 portid = 0;

	अगर (kstrtou16(page, 0, &portid)) अणु
		pr_err("Invalid value '%s' for portid\n", page);
		वापस -EINVAL;
	पूर्ण

	अगर (nvmet_is_port_enabled(port, __func__))
		वापस -EACCES;

	port->disc_addr.portid = cpu_to_le16(portid);
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_, addr_portid);

अटल sमाप_प्रकार nvmet_addr_traddr_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%s\n",
			port->disc_addr.traddr);
पूर्ण

अटल sमाप_प्रकार nvmet_addr_traddr_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	अगर (count > NVMF_TRADDR_SIZE) अणु
		pr_err("Invalid value '%s' for traddr\n", page);
		वापस -EINVAL;
	पूर्ण

	अगर (nvmet_is_port_enabled(port, __func__))
		वापस -EACCES;

	अगर (माला_पूछो(page, "%s\n", port->disc_addr.traddr) != 1)
		वापस -EINVAL;
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_, addr_traddr);

अटल स्थिर काष्ठा nvmet_type_name_map nvmet_addr_treq[] = अणु
	अणु NVMF_TREQ_NOT_SPECIFIED,	"not specified" पूर्ण,
	अणु NVMF_TREQ_REQUIRED,		"required" पूर्ण,
	अणु NVMF_TREQ_NOT_REQUIRED,	"not required" पूर्ण,
पूर्ण;

अटल sमाप_प्रकार nvmet_addr_treq_show(काष्ठा config_item *item, अक्षर *page)
अणु
	u8 treq = to_nvmet_port(item)->disc_addr.treq &
		NVME_TREQ_SECURE_CHANNEL_MASK;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nvmet_addr_treq); i++) अणु
		अगर (treq == nvmet_addr_treq[i].type)
			वापस प्र_लिखो(page, "%s\n", nvmet_addr_treq[i].name);
	पूर्ण

	वापस प्र_लिखो(page, "\n");
पूर्ण

अटल sमाप_प्रकार nvmet_addr_treq_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);
	u8 treq = port->disc_addr.treq & ~NVME_TREQ_SECURE_CHANNEL_MASK;
	पूर्णांक i;

	अगर (nvmet_is_port_enabled(port, __func__))
		वापस -EACCES;

	क्रम (i = 0; i < ARRAY_SIZE(nvmet_addr_treq); i++) अणु
		अगर (sysfs_streq(page, nvmet_addr_treq[i].name))
			जाओ found;
	पूर्ण

	pr_err("Invalid value '%s' for treq\n", page);
	वापस -EINVAL;

found:
	treq |= nvmet_addr_treq[i].type;
	port->disc_addr.treq = treq;
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_, addr_treq);

अटल sमाप_प्रकार nvmet_addr_trsvcid_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%s\n",
			port->disc_addr.trsvcid);
पूर्ण

अटल sमाप_प्रकार nvmet_addr_trsvcid_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	अगर (count > NVMF_TRSVCID_SIZE) अणु
		pr_err("Invalid value '%s' for trsvcid\n", page);
		वापस -EINVAL;
	पूर्ण
	अगर (nvmet_is_port_enabled(port, __func__))
		वापस -EACCES;

	अगर (माला_पूछो(page, "%s\n", port->disc_addr.trsvcid) != 1)
		वापस -EINVAL;
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_, addr_trsvcid);

अटल sमाप_प्रकार nvmet_param_अंतरभूत_data_size_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", port->अंतरभूत_data_size);
पूर्ण

अटल sमाप_प्रकार nvmet_param_अंतरभूत_data_size_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);
	पूर्णांक ret;

	अगर (nvmet_is_port_enabled(port, __func__))
		वापस -EACCES;
	ret = kstrtoपूर्णांक(page, 0, &port->अंतरभूत_data_size);
	अगर (ret) अणु
		pr_err("Invalid value '%s' for inline_data_size\n", page);
		वापस -EINVAL;
	पूर्ण
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_, param_अंतरभूत_data_size);

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
अटल sमाप_प्रकार nvmet_param_pi_enable_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", port->pi_enable);
पूर्ण

अटल sमाप_प्रकार nvmet_param_pi_enable_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);
	bool val;

	अगर (strtobool(page, &val))
		वापस -EINVAL;

	अगर (nvmet_is_port_enabled(port, __func__))
		वापस -EACCES;

	port->pi_enable = val;
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_, param_pi_enable);
#पूर्ण_अगर

अटल sमाप_प्रकार nvmet_addr_trtype_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nvmet_transport); i++) अणु
		अगर (port->disc_addr.trtype == nvmet_transport[i].type)
			वापस प्र_लिखो(page, "%s\n", nvmet_transport[i].name);
	पूर्ण

	वापस प्र_लिखो(page, "\n");
पूर्ण

अटल व्योम nvmet_port_init_tsas_rdma(काष्ठा nvmet_port *port)
अणु
	port->disc_addr.tsas.rdma.qptype = NVMF_RDMA_QPTYPE_CONNECTED;
	port->disc_addr.tsas.rdma.prtype = NVMF_RDMA_PRTYPE_NOT_SPECIFIED;
	port->disc_addr.tsas.rdma.cms = NVMF_RDMA_CMS_RDMA_CM;
पूर्ण

अटल sमाप_प्रकार nvmet_addr_trtype_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);
	पूर्णांक i;

	अगर (nvmet_is_port_enabled(port, __func__))
		वापस -EACCES;

	क्रम (i = 0; i < ARRAY_SIZE(nvmet_transport); i++) अणु
		अगर (sysfs_streq(page, nvmet_transport[i].name))
			जाओ found;
	पूर्ण

	pr_err("Invalid value '%s' for trtype\n", page);
	वापस -EINVAL;

found:
	स_रखो(&port->disc_addr.tsas, 0, NVMF_TSAS_SIZE);
	port->disc_addr.trtype = nvmet_transport[i].type;
	अगर (port->disc_addr.trtype == NVMF_TRTYPE_RDMA)
		nvmet_port_init_tsas_rdma(port);
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_, addr_trtype);

/*
 * Namespace काष्ठाures & file operation functions below
 */
अटल sमाप_प्रकार nvmet_ns_device_path_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", to_nvmet_ns(item)->device_path);
पूर्ण

अटल sमाप_प्रकार nvmet_ns_device_path_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);
	काष्ठा nvmet_subsys *subsys = ns->subsys;
	माप_प्रकार len;
	पूर्णांक ret;

	mutex_lock(&subsys->lock);
	ret = -EBUSY;
	अगर (ns->enabled)
		जाओ out_unlock;

	ret = -EINVAL;
	len = म_खोज(page, "\n");
	अगर (!len)
		जाओ out_unlock;

	kमुक्त(ns->device_path);
	ret = -ENOMEM;
	ns->device_path = kmemdup_nul(page, len, GFP_KERNEL);
	अगर (!ns->device_path)
		जाओ out_unlock;

	mutex_unlock(&subsys->lock);
	वापस count;

out_unlock:
	mutex_unlock(&subsys->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(nvmet_ns_, device_path);

#अगर_घोषित CONFIG_PCI_P2PDMA
अटल sमाप_प्रकार nvmet_ns_p2pmem_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);

	वापस pci_p2pdma_enable_show(page, ns->p2p_dev, ns->use_p2pmem);
पूर्ण

अटल sमाप_प्रकार nvmet_ns_p2pmem_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);
	काष्ठा pci_dev *p2p_dev = शून्य;
	bool use_p2pmem;
	पूर्णांक ret = count;
	पूर्णांक error;

	mutex_lock(&ns->subsys->lock);
	अगर (ns->enabled) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	error = pci_p2pdma_enable_store(page, &p2p_dev, &use_p2pmem);
	अगर (error) अणु
		ret = error;
		जाओ out_unlock;
	पूर्ण

	ns->use_p2pmem = use_p2pmem;
	pci_dev_put(ns->p2p_dev);
	ns->p2p_dev = p2p_dev;

out_unlock:
	mutex_unlock(&ns->subsys->lock);

	वापस ret;
पूर्ण

CONFIGFS_ATTR(nvmet_ns_, p2pmem);
#पूर्ण_अगर /* CONFIG_PCI_P2PDMA */

अटल sमाप_प्रकार nvmet_ns_device_uuid_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%pUb\n", &to_nvmet_ns(item)->uuid);
पूर्ण

अटल sमाप_प्रकार nvmet_ns_device_uuid_store(काष्ठा config_item *item,
					  स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);
	काष्ठा nvmet_subsys *subsys = ns->subsys;
	पूर्णांक ret = 0;

	mutex_lock(&subsys->lock);
	अगर (ns->enabled) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	अगर (uuid_parse(page, &ns->uuid))
		ret = -EINVAL;

out_unlock:
	mutex_unlock(&subsys->lock);
	वापस ret ? ret : count;
पूर्ण

CONFIGFS_ATTR(nvmet_ns_, device_uuid);

अटल sमाप_प्रकार nvmet_ns_device_nguid_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%pUb\n", &to_nvmet_ns(item)->nguid);
पूर्ण

अटल sमाप_प्रकार nvmet_ns_device_nguid_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);
	काष्ठा nvmet_subsys *subsys = ns->subsys;
	u8 nguid[16];
	स्थिर अक्षर *p = page;
	पूर्णांक i;
	पूर्णांक ret = 0;

	mutex_lock(&subsys->lock);
	अगर (ns->enabled) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	क्रम (i = 0; i < 16; i++) अणु
		अगर (p + 2 > page + count) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		अगर (!है_षष्ठादशक(p[0]) || !है_षष्ठादशक(p[1])) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		nguid[i] = (hex_to_bin(p[0]) << 4) | hex_to_bin(p[1]);
		p += 2;

		अगर (*p == '-' || *p == ':')
			p++;
	पूर्ण

	स_नकल(&ns->nguid, nguid, माप(nguid));
out_unlock:
	mutex_unlock(&subsys->lock);
	वापस ret ? ret : count;
पूर्ण

CONFIGFS_ATTR(nvmet_ns_, device_nguid);

अटल sमाप_प्रकार nvmet_ns_ana_grpid_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", to_nvmet_ns(item)->anagrpid);
पूर्ण

अटल sमाप_प्रकार nvmet_ns_ana_grpid_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);
	u32 oldgrpid, newgrpid;
	पूर्णांक ret;

	ret = kstrtou32(page, 0, &newgrpid);
	अगर (ret)
		वापस ret;

	अगर (newgrpid < 1 || newgrpid > NVMET_MAX_ANAGRPS)
		वापस -EINVAL;

	करोwn_ग_लिखो(&nvmet_ana_sem);
	oldgrpid = ns->anagrpid;
	nvmet_ana_group_enabled[newgrpid]++;
	ns->anagrpid = newgrpid;
	nvmet_ana_group_enabled[oldgrpid]--;
	nvmet_ana_chgcnt++;
	up_ग_लिखो(&nvmet_ana_sem);

	nvmet_send_ana_event(ns->subsys, शून्य);
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_ns_, ana_grpid);

अटल sमाप_प्रकार nvmet_ns_enable_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", to_nvmet_ns(item)->enabled);
पूर्ण

अटल sमाप_प्रकार nvmet_ns_enable_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);
	bool enable;
	पूर्णांक ret = 0;

	अगर (strtobool(page, &enable))
		वापस -EINVAL;

	अगर (enable)
		ret = nvmet_ns_enable(ns);
	अन्यथा
		nvmet_ns_disable(ns);

	वापस ret ? ret : count;
पूर्ण

CONFIGFS_ATTR(nvmet_ns_, enable);

अटल sमाप_प्रकार nvmet_ns_buffered_io_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", to_nvmet_ns(item)->buffered_io);
पूर्ण

अटल sमाप_प्रकार nvmet_ns_buffered_io_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);
	bool val;

	अगर (strtobool(page, &val))
		वापस -EINVAL;

	mutex_lock(&ns->subsys->lock);
	अगर (ns->enabled) अणु
		pr_err("disable ns before setting buffered_io value.\n");
		mutex_unlock(&ns->subsys->lock);
		वापस -EINVAL;
	पूर्ण

	ns->buffered_io = val;
	mutex_unlock(&ns->subsys->lock);
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_ns_, buffered_io);

अटल sमाप_प्रकार nvmet_ns_revalidate_size_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);
	bool val;

	अगर (strtobool(page, &val))
		वापस -EINVAL;

	अगर (!val)
		वापस -EINVAL;

	mutex_lock(&ns->subsys->lock);
	अगर (!ns->enabled) अणु
		pr_err("enable ns before revalidate.\n");
		mutex_unlock(&ns->subsys->lock);
		वापस -EINVAL;
	पूर्ण
	nvmet_ns_revalidate(ns);
	mutex_unlock(&ns->subsys->lock);
	वापस count;
पूर्ण

CONFIGFS_ATTR_WO(nvmet_ns_, revalidate_size);

अटल काष्ठा configfs_attribute *nvmet_ns_attrs[] = अणु
	&nvmet_ns_attr_device_path,
	&nvmet_ns_attr_device_nguid,
	&nvmet_ns_attr_device_uuid,
	&nvmet_ns_attr_ana_grpid,
	&nvmet_ns_attr_enable,
	&nvmet_ns_attr_buffered_io,
	&nvmet_ns_attr_revalidate_size,
#अगर_घोषित CONFIG_PCI_P2PDMA
	&nvmet_ns_attr_p2pmem,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल व्योम nvmet_ns_release(काष्ठा config_item *item)
अणु
	काष्ठा nvmet_ns *ns = to_nvmet_ns(item);

	nvmet_ns_मुक्त(ns);
पूर्ण

अटल काष्ठा configfs_item_operations nvmet_ns_item_ops = अणु
	.release		= nvmet_ns_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_ns_type = अणु
	.ct_item_ops		= &nvmet_ns_item_ops,
	.ct_attrs		= nvmet_ns_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *nvmet_ns_make(काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा nvmet_subsys *subsys = namespaces_to_subsys(&group->cg_item);
	काष्ठा nvmet_ns *ns;
	पूर्णांक ret;
	u32 nsid;

	ret = kstrtou32(name, 0, &nsid);
	अगर (ret)
		जाओ out;

	ret = -EINVAL;
	अगर (nsid == 0 || nsid == NVME_NSID_ALL) अणु
		pr_err("invalid nsid %#x", nsid);
		जाओ out;
	पूर्ण

	ret = -ENOMEM;
	ns = nvmet_ns_alloc(subsys, nsid);
	अगर (!ns)
		जाओ out;
	config_group_init_type_name(&ns->group, name, &nvmet_ns_type);

	pr_info("adding nsid %d to subsystem %s\n", nsid, subsys->subsysnqn);

	वापस &ns->group;
out:
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा configfs_group_operations nvmet_namespaces_group_ops = अणु
	.make_group		= nvmet_ns_make,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_namespaces_type = अणु
	.ct_group_ops		= &nvmet_namespaces_group_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_NVME_TARGET_PASSTHRU

अटल sमाप_प्रकार nvmet_passthru_device_path_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item->ci_parent);

	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", subsys->passthru_ctrl_path);
पूर्ण

अटल sमाप_प्रकार nvmet_passthru_device_path_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item->ci_parent);
	माप_प्रकार len;
	पूर्णांक ret;

	mutex_lock(&subsys->lock);

	ret = -EBUSY;
	अगर (subsys->passthru_ctrl)
		जाओ out_unlock;

	ret = -EINVAL;
	len = म_खोज(page, "\n");
	अगर (!len)
		जाओ out_unlock;

	kमुक्त(subsys->passthru_ctrl_path);
	ret = -ENOMEM;
	subsys->passthru_ctrl_path = kstrndup(page, len, GFP_KERNEL);
	अगर (!subsys->passthru_ctrl_path)
		जाओ out_unlock;

	mutex_unlock(&subsys->lock);

	वापस count;
out_unlock:
	mutex_unlock(&subsys->lock);
	वापस ret;
पूर्ण
CONFIGFS_ATTR(nvmet_passthru_, device_path);

अटल sमाप_प्रकार nvmet_passthru_enable_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item->ci_parent);

	वापस प्र_लिखो(page, "%d\n", subsys->passthru_ctrl ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार nvmet_passthru_enable_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item->ci_parent);
	bool enable;
	पूर्णांक ret = 0;

	अगर (strtobool(page, &enable))
		वापस -EINVAL;

	अगर (enable)
		ret = nvmet_passthru_ctrl_enable(subsys);
	अन्यथा
		nvmet_passthru_ctrl_disable(subsys);

	वापस ret ? ret : count;
पूर्ण
CONFIGFS_ATTR(nvmet_passthru_, enable);

अटल sमाप_प्रकार nvmet_passthru_admin_समयout_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", to_subsys(item->ci_parent)->admin_समयout);
पूर्ण

अटल sमाप_प्रकार nvmet_passthru_admin_समयout_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item->ci_parent);
	अचिन्हित पूर्णांक समयout;

	अगर (kstrtouपूर्णांक(page, 0, &समयout))
		वापस -EINVAL;
	subsys->admin_समयout = समयout;
	वापस count;
पूर्ण
CONFIGFS_ATTR(nvmet_passthru_, admin_समयout);

अटल sमाप_प्रकार nvmet_passthru_io_समयout_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", to_subsys(item->ci_parent)->io_समयout);
पूर्ण

अटल sमाप_प्रकार nvmet_passthru_io_समयout_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item->ci_parent);
	अचिन्हित पूर्णांक समयout;

	अगर (kstrtouपूर्णांक(page, 0, &समयout))
		वापस -EINVAL;
	subsys->io_समयout = समयout;
	वापस count;
पूर्ण
CONFIGFS_ATTR(nvmet_passthru_, io_समयout);

अटल काष्ठा configfs_attribute *nvmet_passthru_attrs[] = अणु
	&nvmet_passthru_attr_device_path,
	&nvmet_passthru_attr_enable,
	&nvmet_passthru_attr_admin_समयout,
	&nvmet_passthru_attr_io_समयout,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_passthru_type = अणु
	.ct_attrs		= nvmet_passthru_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल व्योम nvmet_add_passthru_group(काष्ठा nvmet_subsys *subsys)
अणु
	config_group_init_type_name(&subsys->passthru_group,
				    "passthru", &nvmet_passthru_type);
	configfs_add_शेष_group(&subsys->passthru_group,
				   &subsys->group);
पूर्ण

#अन्यथा /* CONFIG_NVME_TARGET_PASSTHRU */

अटल व्योम nvmet_add_passthru_group(काष्ठा nvmet_subsys *subsys)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_NVME_TARGET_PASSTHRU */

अटल पूर्णांक nvmet_port_subsys_allow_link(काष्ठा config_item *parent,
		काष्ठा config_item *target)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(parent->ci_parent);
	काष्ठा nvmet_subsys *subsys;
	काष्ठा nvmet_subsys_link *link, *p;
	पूर्णांक ret;

	अगर (target->ci_type != &nvmet_subsys_type) अणु
		pr_err("can only link subsystems into the subsystems dir.!\n");
		वापस -EINVAL;
	पूर्ण
	subsys = to_subsys(target);
	link = kदो_स्मृति(माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;
	link->subsys = subsys;

	करोwn_ग_लिखो(&nvmet_config_sem);
	ret = -EEXIST;
	list_क्रम_each_entry(p, &port->subप्रणालीs, entry) अणु
		अगर (p->subsys == subsys)
			जाओ out_मुक्त_link;
	पूर्ण

	अगर (list_empty(&port->subप्रणालीs)) अणु
		ret = nvmet_enable_port(port);
		अगर (ret)
			जाओ out_मुक्त_link;
	पूर्ण

	list_add_tail(&link->entry, &port->subप्रणालीs);
	nvmet_port_disc_changed(port, subsys);

	up_ग_लिखो(&nvmet_config_sem);
	वापस 0;

out_मुक्त_link:
	up_ग_लिखो(&nvmet_config_sem);
	kमुक्त(link);
	वापस ret;
पूर्ण

अटल व्योम nvmet_port_subsys_drop_link(काष्ठा config_item *parent,
		काष्ठा config_item *target)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(parent->ci_parent);
	काष्ठा nvmet_subsys *subsys = to_subsys(target);
	काष्ठा nvmet_subsys_link *p;

	करोwn_ग_लिखो(&nvmet_config_sem);
	list_क्रम_each_entry(p, &port->subप्रणालीs, entry) अणु
		अगर (p->subsys == subsys)
			जाओ found;
	पूर्ण
	up_ग_लिखो(&nvmet_config_sem);
	वापस;

found:
	list_del(&p->entry);
	nvmet_port_del_ctrls(port, subsys);
	nvmet_port_disc_changed(port, subsys);

	अगर (list_empty(&port->subप्रणालीs))
		nvmet_disable_port(port);
	up_ग_लिखो(&nvmet_config_sem);
	kमुक्त(p);
पूर्ण

अटल काष्ठा configfs_item_operations nvmet_port_subsys_item_ops = अणु
	.allow_link		= nvmet_port_subsys_allow_link,
	.drop_link		= nvmet_port_subsys_drop_link,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_port_subsys_type = अणु
	.ct_item_ops		= &nvmet_port_subsys_item_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक nvmet_allowed_hosts_allow_link(काष्ठा config_item *parent,
		काष्ठा config_item *target)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(parent->ci_parent);
	काष्ठा nvmet_host *host;
	काष्ठा nvmet_host_link *link, *p;
	पूर्णांक ret;

	अगर (target->ci_type != &nvmet_host_type) अणु
		pr_err("can only link hosts into the allowed_hosts directory!\n");
		वापस -EINVAL;
	पूर्ण

	host = to_host(target);
	link = kदो_स्मृति(माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;
	link->host = host;

	करोwn_ग_लिखो(&nvmet_config_sem);
	ret = -EINVAL;
	अगर (subsys->allow_any_host) अणु
		pr_err("can't add hosts when allow_any_host is set!\n");
		जाओ out_मुक्त_link;
	पूर्ण

	ret = -EEXIST;
	list_क्रम_each_entry(p, &subsys->hosts, entry) अणु
		अगर (!म_भेद(nvmet_host_name(p->host), nvmet_host_name(host)))
			जाओ out_मुक्त_link;
	पूर्ण
	list_add_tail(&link->entry, &subsys->hosts);
	nvmet_subsys_disc_changed(subsys, host);

	up_ग_लिखो(&nvmet_config_sem);
	वापस 0;
out_मुक्त_link:
	up_ग_लिखो(&nvmet_config_sem);
	kमुक्त(link);
	वापस ret;
पूर्ण

अटल व्योम nvmet_allowed_hosts_drop_link(काष्ठा config_item *parent,
		काष्ठा config_item *target)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(parent->ci_parent);
	काष्ठा nvmet_host *host = to_host(target);
	काष्ठा nvmet_host_link *p;

	करोwn_ग_लिखो(&nvmet_config_sem);
	list_क्रम_each_entry(p, &subsys->hosts, entry) अणु
		अगर (!म_भेद(nvmet_host_name(p->host), nvmet_host_name(host)))
			जाओ found;
	पूर्ण
	up_ग_लिखो(&nvmet_config_sem);
	वापस;

found:
	list_del(&p->entry);
	nvmet_subsys_disc_changed(subsys, host);

	up_ग_लिखो(&nvmet_config_sem);
	kमुक्त(p);
पूर्ण

अटल काष्ठा configfs_item_operations nvmet_allowed_hosts_item_ops = अणु
	.allow_link		= nvmet_allowed_hosts_allow_link,
	.drop_link		= nvmet_allowed_hosts_drop_link,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_allowed_hosts_type = अणु
	.ct_item_ops		= &nvmet_allowed_hosts_item_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल sमाप_प्रकार nvmet_subsys_attr_allow_any_host_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n",
		to_subsys(item)->allow_any_host);
पूर्ण

अटल sमाप_प्रकार nvmet_subsys_attr_allow_any_host_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item);
	bool allow_any_host;
	पूर्णांक ret = 0;

	अगर (strtobool(page, &allow_any_host))
		वापस -EINVAL;

	करोwn_ग_लिखो(&nvmet_config_sem);
	अगर (allow_any_host && !list_empty(&subsys->hosts)) अणु
		pr_err("Can't set allow_any_host when explicit hosts are set!\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (subsys->allow_any_host != allow_any_host) अणु
		subsys->allow_any_host = allow_any_host;
		nvmet_subsys_disc_changed(subsys, शून्य);
	पूर्ण

out_unlock:
	up_ग_लिखो(&nvmet_config_sem);
	वापस ret ? ret : count;
पूर्ण

CONFIGFS_ATTR(nvmet_subsys_, attr_allow_any_host);

अटल sमाप_प्रकार nvmet_subsys_attr_version_show(काष्ठा config_item *item,
					      अक्षर *page)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item);

	अगर (NVME_TERTIARY(subsys->ver))
		वापस snम_लिखो(page, PAGE_SIZE, "%llu.%llu.%llu\n",
				NVME_MAJOR(subsys->ver),
				NVME_MINOR(subsys->ver),
				NVME_TERTIARY(subsys->ver));

	वापस snम_लिखो(page, PAGE_SIZE, "%llu.%llu\n",
			NVME_MAJOR(subsys->ver),
			NVME_MINOR(subsys->ver));
पूर्ण

अटल sमाप_प्रकार nvmet_subsys_attr_version_store(काष्ठा config_item *item,
					       स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item);
	पूर्णांक major, minor, tertiary = 0;
	पूर्णांक ret;

	/* passthru subप्रणालीs use the underlying controller's version */
	अगर (nvmet_passthru_ctrl(subsys))
		वापस -EINVAL;

	ret = माला_पूछो(page, "%d.%d.%d\n", &major, &minor, &tertiary);
	अगर (ret != 2 && ret != 3)
		वापस -EINVAL;

	करोwn_ग_लिखो(&nvmet_config_sem);
	subsys->ver = NVME_VS(major, minor, tertiary);
	up_ग_लिखो(&nvmet_config_sem);

	वापस count;
पूर्ण
CONFIGFS_ATTR(nvmet_subsys_, attr_version);

अटल sमाप_प्रकार nvmet_subsys_attr_serial_show(काष्ठा config_item *item,
					     अक्षर *page)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%llx\n", subsys->serial);
पूर्ण

अटल sमाप_प्रकार nvmet_subsys_attr_serial_store(काष्ठा config_item *item,
					      स्थिर अक्षर *page, माप_प्रकार count)
अणु
	u64 serial;

	अगर (माला_पूछो(page, "%llx\n", &serial) != 1)
		वापस -EINVAL;

	करोwn_ग_लिखो(&nvmet_config_sem);
	to_subsys(item)->serial = serial;
	up_ग_लिखो(&nvmet_config_sem);

	वापस count;
पूर्ण
CONFIGFS_ATTR(nvmet_subsys_, attr_serial);

अटल sमाप_प्रकार nvmet_subsys_attr_cntlid_min_show(काष्ठा config_item *item,
						 अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", to_subsys(item)->cntlid_min);
पूर्ण

अटल sमाप_प्रकार nvmet_subsys_attr_cntlid_min_store(काष्ठा config_item *item,
						  स्थिर अक्षर *page, माप_प्रकार cnt)
अणु
	u16 cntlid_min;

	अगर (माला_पूछो(page, "%hu\n", &cntlid_min) != 1)
		वापस -EINVAL;

	अगर (cntlid_min == 0)
		वापस -EINVAL;

	करोwn_ग_लिखो(&nvmet_config_sem);
	अगर (cntlid_min >= to_subsys(item)->cntlid_max)
		जाओ out_unlock;
	to_subsys(item)->cntlid_min = cntlid_min;
	up_ग_लिखो(&nvmet_config_sem);
	वापस cnt;

out_unlock:
	up_ग_लिखो(&nvmet_config_sem);
	वापस -EINVAL;
पूर्ण
CONFIGFS_ATTR(nvmet_subsys_, attr_cntlid_min);

अटल sमाप_प्रकार nvmet_subsys_attr_cntlid_max_show(काष्ठा config_item *item,
						 अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", to_subsys(item)->cntlid_max);
पूर्ण

अटल sमाप_प्रकार nvmet_subsys_attr_cntlid_max_store(काष्ठा config_item *item,
						  स्थिर अक्षर *page, माप_प्रकार cnt)
अणु
	u16 cntlid_max;

	अगर (माला_पूछो(page, "%hu\n", &cntlid_max) != 1)
		वापस -EINVAL;

	अगर (cntlid_max == 0)
		वापस -EINVAL;

	करोwn_ग_लिखो(&nvmet_config_sem);
	अगर (cntlid_max <= to_subsys(item)->cntlid_min)
		जाओ out_unlock;
	to_subsys(item)->cntlid_max = cntlid_max;
	up_ग_लिखो(&nvmet_config_sem);
	वापस cnt;

out_unlock:
	up_ग_लिखो(&nvmet_config_sem);
	वापस -EINVAL;
पूर्ण
CONFIGFS_ATTR(nvmet_subsys_, attr_cntlid_max);

अटल sमाप_प्रकार nvmet_subsys_attr_model_show(काष्ठा config_item *item,
					    अक्षर *page)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item);
	पूर्णांक ret;

	mutex_lock(&subsys->lock);
	ret = snम_लिखो(page, PAGE_SIZE, "%s\n", subsys->model_number ?
			subsys->model_number : NVMET_DEFAULT_CTRL_MODEL);
	mutex_unlock(&subsys->lock);

	वापस ret;
पूर्ण

/* See Section 1.5 of NVMe 1.4 */
अटल bool nvmet_is_ascii(स्थिर अक्षर c)
अणु
	वापस c >= 0x20 && c <= 0x7e;
पूर्ण

अटल sमाप_प्रकार nvmet_subsys_attr_model_store_locked(काष्ठा nvmet_subsys *subsys,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	पूर्णांक pos = 0, len;

	अगर (subsys->model_number) अणु
		pr_err("Can't set model number. %s is already assigned\n",
		       subsys->model_number);
		वापस -EINVAL;
	पूर्ण

	len = म_खोज(page, "\n");
	अगर (!len)
		वापस -EINVAL;

	अगर (len > NVMET_MN_MAX_SIZE) अणु
		pr_err("Model number size can not exceed %d Bytes\n",
		       NVMET_MN_MAX_SIZE);
		वापस -EINVAL;
	पूर्ण

	क्रम (pos = 0; pos < len; pos++) अणु
		अगर (!nvmet_is_ascii(page[pos]))
			वापस -EINVAL;
	पूर्ण

	subsys->model_number = kmemdup_nul(page, len, GFP_KERNEL);
	अगर (!subsys->model_number)
		वापस -ENOMEM;
	वापस count;
पूर्ण

अटल sमाप_प्रकार nvmet_subsys_attr_model_store(काष्ठा config_item *item,
					     स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item);
	sमाप_प्रकार ret;

	करोwn_ग_लिखो(&nvmet_config_sem);
	mutex_lock(&subsys->lock);
	ret = nvmet_subsys_attr_model_store_locked(subsys, page, count);
	mutex_unlock(&subsys->lock);
	up_ग_लिखो(&nvmet_config_sem);

	वापस ret;
पूर्ण
CONFIGFS_ATTR(nvmet_subsys_, attr_model);

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
अटल sमाप_प्रकार nvmet_subsys_attr_pi_enable_show(काष्ठा config_item *item,
						अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", to_subsys(item)->pi_support);
पूर्ण

अटल sमाप_प्रकार nvmet_subsys_attr_pi_enable_store(काष्ठा config_item *item,
						 स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item);
	bool pi_enable;

	अगर (strtobool(page, &pi_enable))
		वापस -EINVAL;

	subsys->pi_support = pi_enable;
	वापस count;
पूर्ण
CONFIGFS_ATTR(nvmet_subsys_, attr_pi_enable);
#पूर्ण_अगर

अटल काष्ठा configfs_attribute *nvmet_subsys_attrs[] = अणु
	&nvmet_subsys_attr_attr_allow_any_host,
	&nvmet_subsys_attr_attr_version,
	&nvmet_subsys_attr_attr_serial,
	&nvmet_subsys_attr_attr_cntlid_min,
	&nvmet_subsys_attr_attr_cntlid_max,
	&nvmet_subsys_attr_attr_model,
#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
	&nvmet_subsys_attr_attr_pi_enable,
#पूर्ण_अगर
	शून्य,
पूर्ण;

/*
 * Subप्रणाली काष्ठाures & folder operation functions below
 */
अटल व्योम nvmet_subsys_release(काष्ठा config_item *item)
अणु
	काष्ठा nvmet_subsys *subsys = to_subsys(item);

	nvmet_subsys_del_ctrls(subsys);
	nvmet_subsys_put(subsys);
पूर्ण

अटल काष्ठा configfs_item_operations nvmet_subsys_item_ops = अणु
	.release		= nvmet_subsys_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_subsys_type = अणु
	.ct_item_ops		= &nvmet_subsys_item_ops,
	.ct_attrs		= nvmet_subsys_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *nvmet_subsys_make(काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा nvmet_subsys *subsys;

	अगर (sysfs_streq(name, NVME_DISC_SUBSYS_NAME)) अणु
		pr_err("can't create discovery subsystem through configfs\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	subsys = nvmet_subsys_alloc(name, NVME_NQN_NVME);
	अगर (IS_ERR(subsys))
		वापस ERR_CAST(subsys);

	config_group_init_type_name(&subsys->group, name, &nvmet_subsys_type);

	config_group_init_type_name(&subsys->namespaces_group,
			"namespaces", &nvmet_namespaces_type);
	configfs_add_शेष_group(&subsys->namespaces_group, &subsys->group);

	config_group_init_type_name(&subsys->allowed_hosts_group,
			"allowed_hosts", &nvmet_allowed_hosts_type);
	configfs_add_शेष_group(&subsys->allowed_hosts_group,
			&subsys->group);

	nvmet_add_passthru_group(subsys);

	वापस &subsys->group;
पूर्ण

अटल काष्ठा configfs_group_operations nvmet_subप्रणालीs_group_ops = अणु
	.make_group		= nvmet_subsys_make,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_subप्रणालीs_type = अणु
	.ct_group_ops		= &nvmet_subप्रणालीs_group_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल sमाप_प्रकार nvmet_referral_enable_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", to_nvmet_port(item)->enabled);
पूर्ण

अटल sमाप_प्रकार nvmet_referral_enable_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_port *parent = to_nvmet_port(item->ci_parent->ci_parent);
	काष्ठा nvmet_port *port = to_nvmet_port(item);
	bool enable;

	अगर (strtobool(page, &enable))
		जाओ inval;

	अगर (enable)
		nvmet_referral_enable(parent, port);
	अन्यथा
		nvmet_referral_disable(parent, port);

	वापस count;
inval:
	pr_err("Invalid value '%s' for enable\n", page);
	वापस -EINVAL;
पूर्ण

CONFIGFS_ATTR(nvmet_referral_, enable);

/*
 * Discovery Service subप्रणाली definitions
 */
अटल काष्ठा configfs_attribute *nvmet_referral_attrs[] = अणु
	&nvmet_attr_addr_adrfam,
	&nvmet_attr_addr_portid,
	&nvmet_attr_addr_treq,
	&nvmet_attr_addr_traddr,
	&nvmet_attr_addr_trsvcid,
	&nvmet_attr_addr_trtype,
	&nvmet_referral_attr_enable,
	शून्य,
पूर्ण;

अटल व्योम nvmet_referral_notअगरy(काष्ठा config_group *group,
		काष्ठा config_item *item)
अणु
	काष्ठा nvmet_port *parent = to_nvmet_port(item->ci_parent->ci_parent);
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	nvmet_referral_disable(parent, port);
पूर्ण

अटल व्योम nvmet_referral_release(काष्ठा config_item *item)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	kमुक्त(port);
पूर्ण

अटल काष्ठा configfs_item_operations nvmet_referral_item_ops = अणु
	.release	= nvmet_referral_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_referral_type = अणु
	.ct_owner	= THIS_MODULE,
	.ct_attrs	= nvmet_referral_attrs,
	.ct_item_ops	= &nvmet_referral_item_ops,
पूर्ण;

अटल काष्ठा config_group *nvmet_referral_make(
		काष्ठा config_group *group, स्थिर अक्षर *name)
अणु
	काष्ठा nvmet_port *port;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&port->entry);
	config_group_init_type_name(&port->group, name, &nvmet_referral_type);

	वापस &port->group;
पूर्ण

अटल काष्ठा configfs_group_operations nvmet_referral_group_ops = अणु
	.make_group		= nvmet_referral_make,
	.disconnect_notअगरy	= nvmet_referral_notअगरy,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_referrals_type = अणु
	.ct_owner	= THIS_MODULE,
	.ct_group_ops	= &nvmet_referral_group_ops,
पूर्ण;

अटल काष्ठा nvmet_type_name_map nvmet_ana_state[] = अणु
	अणु NVME_ANA_OPTIMIZED,		"optimized" पूर्ण,
	अणु NVME_ANA_NONOPTIMIZED,	"non-optimized" पूर्ण,
	अणु NVME_ANA_INACCESSIBLE,	"inaccessible" पूर्ण,
	अणु NVME_ANA_PERSISTENT_LOSS,	"persistent-loss" पूर्ण,
	अणु NVME_ANA_CHANGE,		"change" पूर्ण,
पूर्ण;

अटल sमाप_प्रकार nvmet_ana_group_ana_state_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा nvmet_ana_group *grp = to_ana_group(item);
	क्रमागत nvme_ana_state state = grp->port->ana_state[grp->grpid];
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nvmet_ana_state); i++) अणु
		अगर (state == nvmet_ana_state[i].type)
			वापस प्र_लिखो(page, "%s\n", nvmet_ana_state[i].name);
	पूर्ण

	वापस प्र_लिखो(page, "\n");
पूर्ण

अटल sमाप_प्रकार nvmet_ana_group_ana_state_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा nvmet_ana_group *grp = to_ana_group(item);
	क्रमागत nvme_ana_state *ana_state = grp->port->ana_state;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nvmet_ana_state); i++) अणु
		अगर (sysfs_streq(page, nvmet_ana_state[i].name))
			जाओ found;
	पूर्ण

	pr_err("Invalid value '%s' for ana_state\n", page);
	वापस -EINVAL;

found:
	करोwn_ग_लिखो(&nvmet_ana_sem);
	ana_state[grp->grpid] = (क्रमागत nvme_ana_state) nvmet_ana_state[i].type;
	nvmet_ana_chgcnt++;
	up_ग_लिखो(&nvmet_ana_sem);
	nvmet_port_send_ana_event(grp->port);
	वापस count;
पूर्ण

CONFIGFS_ATTR(nvmet_ana_group_, ana_state);

अटल काष्ठा configfs_attribute *nvmet_ana_group_attrs[] = अणु
	&nvmet_ana_group_attr_ana_state,
	शून्य,
पूर्ण;

अटल व्योम nvmet_ana_group_release(काष्ठा config_item *item)
अणु
	काष्ठा nvmet_ana_group *grp = to_ana_group(item);

	अगर (grp == &grp->port->ana_शेष_group)
		वापस;

	करोwn_ग_लिखो(&nvmet_ana_sem);
	grp->port->ana_state[grp->grpid] = NVME_ANA_INACCESSIBLE;
	nvmet_ana_group_enabled[grp->grpid]--;
	up_ग_लिखो(&nvmet_ana_sem);

	nvmet_port_send_ana_event(grp->port);
	kमुक्त(grp);
पूर्ण

अटल काष्ठा configfs_item_operations nvmet_ana_group_item_ops = अणु
	.release		= nvmet_ana_group_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_ana_group_type = अणु
	.ct_item_ops		= &nvmet_ana_group_item_ops,
	.ct_attrs		= nvmet_ana_group_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *nvmet_ana_groups_make_group(
		काष्ठा config_group *group, स्थिर अक्षर *name)
अणु
	काष्ठा nvmet_port *port = ana_groups_to_port(&group->cg_item);
	काष्ठा nvmet_ana_group *grp;
	u32 grpid;
	पूर्णांक ret;

	ret = kstrtou32(name, 0, &grpid);
	अगर (ret)
		जाओ out;

	ret = -EINVAL;
	अगर (grpid <= 1 || grpid > NVMET_MAX_ANAGRPS)
		जाओ out;

	ret = -ENOMEM;
	grp = kzalloc(माप(*grp), GFP_KERNEL);
	अगर (!grp)
		जाओ out;
	grp->port = port;
	grp->grpid = grpid;

	करोwn_ग_लिखो(&nvmet_ana_sem);
	nvmet_ana_group_enabled[grpid]++;
	up_ग_लिखो(&nvmet_ana_sem);

	nvmet_port_send_ana_event(grp->port);

	config_group_init_type_name(&grp->group, name, &nvmet_ana_group_type);
	वापस &grp->group;
out:
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा configfs_group_operations nvmet_ana_groups_group_ops = अणु
	.make_group		= nvmet_ana_groups_make_group,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_ana_groups_type = अणु
	.ct_group_ops		= &nvmet_ana_groups_group_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Ports definitions.
 */
अटल व्योम nvmet_port_release(काष्ठा config_item *item)
अणु
	काष्ठा nvmet_port *port = to_nvmet_port(item);

	list_del(&port->global_entry);

	kमुक्त(port->ana_state);
	kमुक्त(port);
पूर्ण

अटल काष्ठा configfs_attribute *nvmet_port_attrs[] = अणु
	&nvmet_attr_addr_adrfam,
	&nvmet_attr_addr_treq,
	&nvmet_attr_addr_traddr,
	&nvmet_attr_addr_trsvcid,
	&nvmet_attr_addr_trtype,
	&nvmet_attr_param_अंतरभूत_data_size,
#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
	&nvmet_attr_param_pi_enable,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल काष्ठा configfs_item_operations nvmet_port_item_ops = अणु
	.release		= nvmet_port_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_port_type = अणु
	.ct_attrs		= nvmet_port_attrs,
	.ct_item_ops		= &nvmet_port_item_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *nvmet_ports_make(काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा nvmet_port *port;
	u16 portid;
	u32 i;

	अगर (kstrtou16(name, 0, &portid))
		वापस ERR_PTR(-EINVAL);

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस ERR_PTR(-ENOMEM);

	port->ana_state = kसुस्मृति(NVMET_MAX_ANAGRPS + 1,
			माप(*port->ana_state), GFP_KERNEL);
	अगर (!port->ana_state) अणु
		kमुक्त(port);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 1; i <= NVMET_MAX_ANAGRPS; i++) अणु
		अगर (i == NVMET_DEFAULT_ANA_GRPID)
			port->ana_state[1] = NVME_ANA_OPTIMIZED;
		अन्यथा
			port->ana_state[i] = NVME_ANA_INACCESSIBLE;
	पूर्ण

	list_add(&port->global_entry, &nvmet_ports_list);

	INIT_LIST_HEAD(&port->entry);
	INIT_LIST_HEAD(&port->subप्रणालीs);
	INIT_LIST_HEAD(&port->referrals);
	port->अंतरभूत_data_size = -1;	/* < 0 == let the transport choose */

	port->disc_addr.portid = cpu_to_le16(portid);
	port->disc_addr.adrfam = NVMF_ADDR_FAMILY_MAX;
	port->disc_addr.treq = NVMF_TREQ_DISABLE_SQFLOW;
	config_group_init_type_name(&port->group, name, &nvmet_port_type);

	config_group_init_type_name(&port->subsys_group,
			"subsystems", &nvmet_port_subsys_type);
	configfs_add_शेष_group(&port->subsys_group, &port->group);

	config_group_init_type_name(&port->referrals_group,
			"referrals", &nvmet_referrals_type);
	configfs_add_शेष_group(&port->referrals_group, &port->group);

	config_group_init_type_name(&port->ana_groups_group,
			"ana_groups", &nvmet_ana_groups_type);
	configfs_add_शेष_group(&port->ana_groups_group, &port->group);

	port->ana_शेष_group.port = port;
	port->ana_शेष_group.grpid = NVMET_DEFAULT_ANA_GRPID;
	config_group_init_type_name(&port->ana_शेष_group.group,
			__stringअगरy(NVMET_DEFAULT_ANA_GRPID),
			&nvmet_ana_group_type);
	configfs_add_शेष_group(&port->ana_शेष_group.group,
			&port->ana_groups_group);

	वापस &port->group;
पूर्ण

अटल काष्ठा configfs_group_operations nvmet_ports_group_ops = अणु
	.make_group		= nvmet_ports_make,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_ports_type = अणु
	.ct_group_ops		= &nvmet_ports_group_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group nvmet_subप्रणालीs_group;
अटल काष्ठा config_group nvmet_ports_group;

अटल व्योम nvmet_host_release(काष्ठा config_item *item)
अणु
	काष्ठा nvmet_host *host = to_host(item);

	kमुक्त(host);
पूर्ण

अटल काष्ठा configfs_item_operations nvmet_host_item_ops = अणु
	.release		= nvmet_host_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_host_type = अणु
	.ct_item_ops		= &nvmet_host_item_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *nvmet_hosts_make_group(काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा nvmet_host *host;

	host = kzalloc(माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस ERR_PTR(-ENOMEM);

	config_group_init_type_name(&host->group, name, &nvmet_host_type);

	वापस &host->group;
पूर्ण

अटल काष्ठा configfs_group_operations nvmet_hosts_group_ops = अणु
	.make_group		= nvmet_hosts_make_group,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nvmet_hosts_type = अणु
	.ct_group_ops		= &nvmet_hosts_group_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group nvmet_hosts_group;

अटल स्थिर काष्ठा config_item_type nvmet_root_type = अणु
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली nvmet_configfs_subप्रणाली = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf	= "nvmet",
			.ci_type	= &nvmet_root_type,
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक __init nvmet_init_configfs(व्योम)
अणु
	पूर्णांक ret;

	config_group_init(&nvmet_configfs_subप्रणाली.su_group);
	mutex_init(&nvmet_configfs_subप्रणाली.su_mutex);

	config_group_init_type_name(&nvmet_subप्रणालीs_group,
			"subsystems", &nvmet_subप्रणालीs_type);
	configfs_add_शेष_group(&nvmet_subप्रणालीs_group,
			&nvmet_configfs_subप्रणाली.su_group);

	config_group_init_type_name(&nvmet_ports_group,
			"ports", &nvmet_ports_type);
	configfs_add_शेष_group(&nvmet_ports_group,
			&nvmet_configfs_subप्रणाली.su_group);

	config_group_init_type_name(&nvmet_hosts_group,
			"hosts", &nvmet_hosts_type);
	configfs_add_शेष_group(&nvmet_hosts_group,
			&nvmet_configfs_subप्रणाली.su_group);

	ret = configfs_रेजिस्टर_subप्रणाली(&nvmet_configfs_subप्रणाली);
	अगर (ret) अणु
		pr_err("configfs_register_subsystem: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __निकास nvmet_निकास_configfs(व्योम)
अणु
	configfs_unरेजिस्टर_subप्रणाली(&nvmet_configfs_subप्रणाली);
पूर्ण
