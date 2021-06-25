<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Generic netlink support functions to configure an SMC-R PNET table
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Thomas Richter <पंचांगricht@linux.vnet.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mutex.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>

#समावेश <uapi/linux/अगर.h>
#समावेश <uapi/linux/smc.h>

#समावेश <rdma/ib_verbs.h>

#समावेश <net/netns/generic.h>
#समावेश "smc_netns.h"

#समावेश "smc_pnet.h"
#समावेश "smc_ib.h"
#समावेश "smc_ism.h"
#समावेश "smc_core.h"

अटल काष्ठा net_device *__pnet_find_base_ndev(काष्ठा net_device *ndev);
अटल काष्ठा net_device *pnet_find_base_ndev(काष्ठा net_device *ndev);

अटल स्थिर काष्ठा nla_policy smc_pnet_policy[SMC_PNETID_MAX + 1] = अणु
	[SMC_PNETID_NAME] = अणु
		.type = NLA_NUL_STRING,
		.len = SMC_MAX_PNETID_LEN
	पूर्ण,
	[SMC_PNETID_ETHNAME] = अणु
		.type = NLA_NUL_STRING,
		.len = IFNAMSIZ - 1
	पूर्ण,
	[SMC_PNETID_IBNAME] = अणु
		.type = NLA_NUL_STRING,
		.len = IB_DEVICE_NAME_MAX - 1
	पूर्ण,
	[SMC_PNETID_IBPORT] = अणु .type = NLA_U8 पूर्ण
पूर्ण;

अटल काष्ठा genl_family smc_pnet_nl_family;

क्रमागत smc_pnet_nametype अणु
	SMC_PNET_ETH	= 1,
	SMC_PNET_IB	= 2,
पूर्ण;

/* pnet entry stored in pnet table */
काष्ठा smc_pnetentry अणु
	काष्ठा list_head list;
	अक्षर pnet_name[SMC_MAX_PNETID_LEN + 1];
	क्रमागत smc_pnet_nametype type;
	जोड़ अणु
		काष्ठा अणु
			अक्षर eth_name[IFNAMSIZ + 1];
			काष्ठा net_device *ndev;
		पूर्ण;
		काष्ठा अणु
			अक्षर ib_name[IB_DEVICE_NAME_MAX + 1];
			u8 ib_port;
		पूर्ण;
	पूर्ण;
पूर्ण;

/* Check अगर the pnetid is set */
bool smc_pnet_is_pnetid_set(u8 *pnetid)
अणु
	अगर (pnetid[0] == 0 || pnetid[0] == _S)
		वापस false;
	वापस true;
पूर्ण

/* Check अगर two given pnetids match */
अटल bool smc_pnet_match(u8 *pnetid1, u8 *pnetid2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SMC_MAX_PNETID_LEN; i++) अणु
		अगर ((pnetid1[i] == 0 || pnetid1[i] == _S) &&
		    (pnetid2[i] == 0 || pnetid2[i] == _S))
			अवरोध;
		अगर (pnetid1[i] != pnetid2[i])
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* Remove a pnetid from the pnet table.
 */
अटल पूर्णांक smc_pnet_हटाओ_by_pnetid(काष्ठा net *net, अक्षर *pnet_name)
अणु
	काष्ठा smc_pnetentry *pnetelem, *पंचांगp_pe;
	काष्ठा smc_pnettable *pnettable;
	काष्ठा smc_ib_device *ibdev;
	काष्ठा smcd_dev *smcd_dev;
	काष्ठा smc_net *sn;
	पूर्णांक rc = -ENOENT;
	पूर्णांक ibport;

	/* get pnettable क्रम namespace */
	sn = net_generic(net, smc_net_id);
	pnettable = &sn->pnettable;

	/* हटाओ table entry */
	ग_लिखो_lock(&pnettable->lock);
	list_क्रम_each_entry_safe(pnetelem, पंचांगp_pe, &pnettable->pnetlist,
				 list) अणु
		अगर (!pnet_name ||
		    smc_pnet_match(pnetelem->pnet_name, pnet_name)) अणु
			list_del(&pnetelem->list);
			अगर (pnetelem->type == SMC_PNET_ETH && pnetelem->ndev) अणु
				dev_put(pnetelem->ndev);
				pr_warn_ratelimited("smc: net device %s "
						    "erased user defined "
						    "pnetid %.16s\n",
						    pnetelem->eth_name,
						    pnetelem->pnet_name);
			पूर्ण
			kमुक्त(pnetelem);
			rc = 0;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&pnettable->lock);

	/* अगर this is not the initial namespace, stop here */
	अगर (net != &init_net)
		वापस rc;

	/* हटाओ ib devices */
	mutex_lock(&smc_ib_devices.mutex);
	list_क्रम_each_entry(ibdev, &smc_ib_devices.list, list) अणु
		क्रम (ibport = 0; ibport < SMC_MAX_PORTS; ibport++) अणु
			अगर (ibdev->pnetid_by_user[ibport] &&
			    (!pnet_name ||
			     smc_pnet_match(pnet_name,
					    ibdev->pnetid[ibport]))) अणु
				pr_warn_ratelimited("smc: ib device %s ibport "
						    "%d erased user defined "
						    "pnetid %.16s\n",
						    ibdev->ibdev->name,
						    ibport + 1,
						    ibdev->pnetid[ibport]);
				स_रखो(ibdev->pnetid[ibport], 0,
				       SMC_MAX_PNETID_LEN);
				ibdev->pnetid_by_user[ibport] = false;
				rc = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&smc_ib_devices.mutex);
	/* हटाओ smcd devices */
	mutex_lock(&smcd_dev_list.mutex);
	list_क्रम_each_entry(smcd_dev, &smcd_dev_list.list, list) अणु
		अगर (smcd_dev->pnetid_by_user &&
		    (!pnet_name ||
		     smc_pnet_match(pnet_name, smcd_dev->pnetid))) अणु
			pr_warn_ratelimited("smc: smcd device %s "
					    "erased user defined pnetid "
					    "%.16s\n", dev_name(&smcd_dev->dev),
					    smcd_dev->pnetid);
			स_रखो(smcd_dev->pnetid, 0, SMC_MAX_PNETID_LEN);
			smcd_dev->pnetid_by_user = false;
			rc = 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&smcd_dev_list.mutex);
	वापस rc;
पूर्ण

/* Add the reference to a given network device to the pnet table.
 */
अटल पूर्णांक smc_pnet_add_by_ndev(काष्ठा net_device *ndev)
अणु
	काष्ठा smc_pnetentry *pnetelem, *पंचांगp_pe;
	काष्ठा smc_pnettable *pnettable;
	काष्ठा net *net = dev_net(ndev);
	काष्ठा smc_net *sn;
	पूर्णांक rc = -ENOENT;

	/* get pnettable क्रम namespace */
	sn = net_generic(net, smc_net_id);
	pnettable = &sn->pnettable;

	ग_लिखो_lock(&pnettable->lock);
	list_क्रम_each_entry_safe(pnetelem, पंचांगp_pe, &pnettable->pnetlist, list) अणु
		अगर (pnetelem->type == SMC_PNET_ETH && !pnetelem->ndev &&
		    !म_भेदन(pnetelem->eth_name, ndev->name, IFNAMSIZ)) अणु
			dev_hold(ndev);
			pnetelem->ndev = ndev;
			rc = 0;
			pr_warn_ratelimited("smc: adding net device %s with "
					    "user defined pnetid %.16s\n",
					    pnetelem->eth_name,
					    pnetelem->pnet_name);
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&pnettable->lock);
	वापस rc;
पूर्ण

/* Remove the reference to a given network device from the pnet table.
 */
अटल पूर्णांक smc_pnet_हटाओ_by_ndev(काष्ठा net_device *ndev)
अणु
	काष्ठा smc_pnetentry *pnetelem, *पंचांगp_pe;
	काष्ठा smc_pnettable *pnettable;
	काष्ठा net *net = dev_net(ndev);
	काष्ठा smc_net *sn;
	पूर्णांक rc = -ENOENT;

	/* get pnettable क्रम namespace */
	sn = net_generic(net, smc_net_id);
	pnettable = &sn->pnettable;

	ग_लिखो_lock(&pnettable->lock);
	list_क्रम_each_entry_safe(pnetelem, पंचांगp_pe, &pnettable->pnetlist, list) अणु
		अगर (pnetelem->type == SMC_PNET_ETH && pnetelem->ndev == ndev) अणु
			dev_put(pnetelem->ndev);
			pnetelem->ndev = शून्य;
			rc = 0;
			pr_warn_ratelimited("smc: removing net device %s with "
					    "user defined pnetid %.16s\n",
					    pnetelem->eth_name,
					    pnetelem->pnet_name);
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&pnettable->lock);
	वापस rc;
पूर्ण

/* Apply pnetid to ib device when no pnetid is set.
 */
अटल bool smc_pnet_apply_ib(काष्ठा smc_ib_device *ib_dev, u8 ib_port,
			      अक्षर *pnet_name)
अणु
	bool applied = false;

	mutex_lock(&smc_ib_devices.mutex);
	अगर (!smc_pnet_is_pnetid_set(ib_dev->pnetid[ib_port - 1])) अणु
		स_नकल(ib_dev->pnetid[ib_port - 1], pnet_name,
		       SMC_MAX_PNETID_LEN);
		ib_dev->pnetid_by_user[ib_port - 1] = true;
		applied = true;
	पूर्ण
	mutex_unlock(&smc_ib_devices.mutex);
	वापस applied;
पूर्ण

/* Apply pnetid to smcd device when no pnetid is set.
 */
अटल bool smc_pnet_apply_smcd(काष्ठा smcd_dev *smcd_dev, अक्षर *pnet_name)
अणु
	bool applied = false;

	mutex_lock(&smcd_dev_list.mutex);
	अगर (!smc_pnet_is_pnetid_set(smcd_dev->pnetid)) अणु
		स_नकल(smcd_dev->pnetid, pnet_name, SMC_MAX_PNETID_LEN);
		smcd_dev->pnetid_by_user = true;
		applied = true;
	पूर्ण
	mutex_unlock(&smcd_dev_list.mutex);
	वापस applied;
पूर्ण

/* The limit क्रम pnetid is 16 अक्षरacters.
 * Valid अक्षरacters should be (single-byte अक्षरacter set) a-z, A-Z, 0-9.
 * Lower हाल letters are converted to upper हाल.
 * Interior blanks should not be used.
 */
अटल bool smc_pnetid_valid(स्थिर अक्षर *pnet_name, अक्षर *pnetid)
अणु
	अक्षर *bf = skip_spaces(pnet_name);
	माप_प्रकार len = म_माप(bf);
	अक्षर *end = bf + len;

	अगर (!len)
		वापस false;
	जबतक (--end >= bf && है_खाली(*end))
		;
	अगर (end - bf >= SMC_MAX_PNETID_LEN)
		वापस false;
	जबतक (bf <= end) अणु
		अगर (!है_अक्षर_अंक(*bf))
			वापस false;
		*pnetid++ = है_छोटा(*bf) ? बड़े(*bf) : *bf;
		bf++;
	पूर्ण
	*pnetid = '\0';
	वापस true;
पूर्ण

/* Find an infiniband device by a given name. The device might not exist. */
अटल काष्ठा smc_ib_device *smc_pnet_find_ib(अक्षर *ib_name)
अणु
	काष्ठा smc_ib_device *ibdev;

	mutex_lock(&smc_ib_devices.mutex);
	list_क्रम_each_entry(ibdev, &smc_ib_devices.list, list) अणु
		अगर (!म_भेदन(ibdev->ibdev->name, ib_name,
			     माप(ibdev->ibdev->name)) ||
		    !म_भेदन(dev_name(ibdev->ibdev->dev.parent), ib_name,
			     IB_DEVICE_NAME_MAX - 1)) अणु
			जाओ out;
		पूर्ण
	पूर्ण
	ibdev = शून्य;
out:
	mutex_unlock(&smc_ib_devices.mutex);
	वापस ibdev;
पूर्ण

/* Find an smcd device by a given name. The device might not exist. */
अटल काष्ठा smcd_dev *smc_pnet_find_smcd(अक्षर *smcd_name)
अणु
	काष्ठा smcd_dev *smcd_dev;

	mutex_lock(&smcd_dev_list.mutex);
	list_क्रम_each_entry(smcd_dev, &smcd_dev_list.list, list) अणु
		अगर (!म_भेदन(dev_name(&smcd_dev->dev), smcd_name,
			     IB_DEVICE_NAME_MAX - 1))
			जाओ out;
	पूर्ण
	smcd_dev = शून्य;
out:
	mutex_unlock(&smcd_dev_list.mutex);
	वापस smcd_dev;
पूर्ण

अटल पूर्णांक smc_pnet_add_eth(काष्ठा smc_pnettable *pnettable, काष्ठा net *net,
			    अक्षर *eth_name, अक्षर *pnet_name)
अणु
	काष्ठा smc_pnetentry *पंचांगp_pe, *new_pe;
	काष्ठा net_device *ndev, *base_ndev;
	u8 ndev_pnetid[SMC_MAX_PNETID_LEN];
	bool new_netdev;
	पूर्णांक rc;

	/* check अगर (base) netdev alपढ़ोy has a pnetid. If there is one, we करो
	 * not want to add a pnet table entry
	 */
	rc = -EEXIST;
	ndev = dev_get_by_name(net, eth_name);	/* dev_hold() */
	अगर (ndev) अणु
		base_ndev = pnet_find_base_ndev(ndev);
		अगर (!smc_pnetid_by_dev_port(base_ndev->dev.parent,
					    base_ndev->dev_port, ndev_pnetid))
			जाओ out_put;
	पूर्ण

	/* add a new netdev entry to the pnet table अगर there isn't one */
	rc = -ENOMEM;
	new_pe = kzalloc(माप(*new_pe), GFP_KERNEL);
	अगर (!new_pe)
		जाओ out_put;
	new_pe->type = SMC_PNET_ETH;
	स_नकल(new_pe->pnet_name, pnet_name, SMC_MAX_PNETID_LEN);
	म_नकलन(new_pe->eth_name, eth_name, IFNAMSIZ);
	new_pe->ndev = ndev;

	rc = -EEXIST;
	new_netdev = true;
	ग_लिखो_lock(&pnettable->lock);
	list_क्रम_each_entry(पंचांगp_pe, &pnettable->pnetlist, list) अणु
		अगर (पंचांगp_pe->type == SMC_PNET_ETH &&
		    !म_भेदन(पंचांगp_pe->eth_name, eth_name, IFNAMSIZ)) अणु
			new_netdev = false;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (new_netdev) अणु
		list_add_tail(&new_pe->list, &pnettable->pnetlist);
		ग_लिखो_unlock(&pnettable->lock);
	पूर्ण अन्यथा अणु
		ग_लिखो_unlock(&pnettable->lock);
		kमुक्त(new_pe);
		जाओ out_put;
	पूर्ण
	अगर (ndev)
		pr_warn_ratelimited("smc: net device %s "
				    "applied user defined pnetid %.16s\n",
				    new_pe->eth_name, new_pe->pnet_name);
	वापस 0;

out_put:
	अगर (ndev)
		dev_put(ndev);
	वापस rc;
पूर्ण

अटल पूर्णांक smc_pnet_add_ib(काष्ठा smc_pnettable *pnettable, अक्षर *ib_name,
			   u8 ib_port, अक्षर *pnet_name)
अणु
	काष्ठा smc_pnetentry *पंचांगp_pe, *new_pe;
	काष्ठा smc_ib_device *ib_dev;
	bool smcddev_applied = true;
	bool ibdev_applied = true;
	काष्ठा smcd_dev *smcd_dev;
	bool new_ibdev;

	/* try to apply the pnetid to active devices */
	ib_dev = smc_pnet_find_ib(ib_name);
	अगर (ib_dev) अणु
		ibdev_applied = smc_pnet_apply_ib(ib_dev, ib_port, pnet_name);
		अगर (ibdev_applied)
			pr_warn_ratelimited("smc: ib device %s ibport %d "
					    "applied user defined pnetid "
					    "%.16s\n", ib_dev->ibdev->name,
					    ib_port,
					    ib_dev->pnetid[ib_port - 1]);
	पूर्ण
	smcd_dev = smc_pnet_find_smcd(ib_name);
	अगर (smcd_dev) अणु
		smcddev_applied = smc_pnet_apply_smcd(smcd_dev, pnet_name);
		अगर (smcddev_applied)
			pr_warn_ratelimited("smc: smcd device %s "
					    "applied user defined pnetid "
					    "%.16s\n", dev_name(&smcd_dev->dev),
					    smcd_dev->pnetid);
	पूर्ण
	/* Apply fails when a device has a hardware-defined pnetid set, करो not
	 * add a pnet table entry in that हाल.
	 */
	अगर (!ibdev_applied || !smcddev_applied)
		वापस -EEXIST;

	/* add a new ib entry to the pnet table अगर there isn't one */
	new_pe = kzalloc(माप(*new_pe), GFP_KERNEL);
	अगर (!new_pe)
		वापस -ENOMEM;
	new_pe->type = SMC_PNET_IB;
	स_नकल(new_pe->pnet_name, pnet_name, SMC_MAX_PNETID_LEN);
	म_नकलन(new_pe->ib_name, ib_name, IB_DEVICE_NAME_MAX);
	new_pe->ib_port = ib_port;

	new_ibdev = true;
	ग_लिखो_lock(&pnettable->lock);
	list_क्रम_each_entry(पंचांगp_pe, &pnettable->pnetlist, list) अणु
		अगर (पंचांगp_pe->type == SMC_PNET_IB &&
		    !म_भेदन(पंचांगp_pe->ib_name, ib_name, IB_DEVICE_NAME_MAX)) अणु
			new_ibdev = false;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (new_ibdev) अणु
		list_add_tail(&new_pe->list, &pnettable->pnetlist);
		ग_लिखो_unlock(&pnettable->lock);
	पूर्ण अन्यथा अणु
		ग_लिखो_unlock(&pnettable->lock);
		kमुक्त(new_pe);
	पूर्ण
	वापस (new_ibdev) ? 0 : -EEXIST;
पूर्ण

/* Append a pnetid to the end of the pnet table अगर not alपढ़ोy on this list.
 */
अटल पूर्णांक smc_pnet_enter(काष्ठा net *net, काष्ठा nlattr *tb[])
अणु
	अक्षर pnet_name[SMC_MAX_PNETID_LEN + 1];
	काष्ठा smc_pnettable *pnettable;
	bool new_netdev = false;
	bool new_ibdev = false;
	काष्ठा smc_net *sn;
	u8 ibport = 1;
	अक्षर *string;
	पूर्णांक rc;

	/* get pnettable क्रम namespace */
	sn = net_generic(net, smc_net_id);
	pnettable = &sn->pnettable;

	rc = -EINVAL;
	अगर (!tb[SMC_PNETID_NAME])
		जाओ error;
	string = (अक्षर *)nla_data(tb[SMC_PNETID_NAME]);
	अगर (!smc_pnetid_valid(string, pnet_name))
		जाओ error;

	अगर (tb[SMC_PNETID_ETHNAME]) अणु
		string = (अक्षर *)nla_data(tb[SMC_PNETID_ETHNAME]);
		rc = smc_pnet_add_eth(pnettable, net, string, pnet_name);
		अगर (!rc)
			new_netdev = true;
		अन्यथा अगर (rc != -EEXIST)
			जाओ error;
	पूर्ण

	/* अगर this is not the initial namespace, stop here */
	अगर (net != &init_net)
		वापस new_netdev ? 0 : -EEXIST;

	rc = -EINVAL;
	अगर (tb[SMC_PNETID_IBNAME]) अणु
		string = (अक्षर *)nla_data(tb[SMC_PNETID_IBNAME]);
		string = strim(string);
		अगर (tb[SMC_PNETID_IBPORT]) अणु
			ibport = nla_get_u8(tb[SMC_PNETID_IBPORT]);
			अगर (ibport < 1 || ibport > SMC_MAX_PORTS)
				जाओ error;
		पूर्ण
		rc = smc_pnet_add_ib(pnettable, string, ibport, pnet_name);
		अगर (!rc)
			new_ibdev = true;
		अन्यथा अगर (rc != -EEXIST)
			जाओ error;
	पूर्ण
	वापस (new_netdev || new_ibdev) ? 0 : -EEXIST;

error:
	वापस rc;
पूर्ण

/* Convert an smc_pnetentry to a netlink attribute sequence */
अटल पूर्णांक smc_pnet_set_nla(काष्ठा sk_buff *msg,
			    काष्ठा smc_pnetentry *pnetelem)
अणु
	अगर (nla_put_string(msg, SMC_PNETID_NAME, pnetelem->pnet_name))
		वापस -1;
	अगर (pnetelem->type == SMC_PNET_ETH) अणु
		अगर (nla_put_string(msg, SMC_PNETID_ETHNAME,
				   pnetelem->eth_name))
			वापस -1;
	पूर्ण अन्यथा अणु
		अगर (nla_put_string(msg, SMC_PNETID_ETHNAME, "n/a"))
			वापस -1;
	पूर्ण
	अगर (pnetelem->type == SMC_PNET_IB) अणु
		अगर (nla_put_string(msg, SMC_PNETID_IBNAME, pnetelem->ib_name) ||
		    nla_put_u8(msg, SMC_PNETID_IBPORT, pnetelem->ib_port))
			वापस -1;
	पूर्ण अन्यथा अणु
		अगर (nla_put_string(msg, SMC_PNETID_IBNAME, "n/a") ||
		    nla_put_u8(msg, SMC_PNETID_IBPORT, 0xff))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smc_pnet_add(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);

	वापस smc_pnet_enter(net, info->attrs);
पूर्ण

अटल पूर्णांक smc_pnet_del(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);

	अगर (!info->attrs[SMC_PNETID_NAME])
		वापस -EINVAL;
	वापस smc_pnet_हटाओ_by_pnetid(net,
				(अक्षर *)nla_data(info->attrs[SMC_PNETID_NAME]));
पूर्ण

अटल पूर्णांक smc_pnet_dump_start(काष्ठा netlink_callback *cb)
अणु
	cb->args[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक smc_pnet_dumpinfo(काष्ठा sk_buff *skb,
			     u32 portid, u32 seq, u32 flags,
			     काष्ठा smc_pnetentry *pnetelem)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(skb, portid, seq, &smc_pnet_nl_family,
			  flags, SMC_PNETID_GET);
	अगर (!hdr)
		वापस -ENOMEM;
	अगर (smc_pnet_set_nla(skb, pnetelem) < 0) अणु
		genlmsg_cancel(skb, hdr);
		वापस -EMSGSIZE;
	पूर्ण
	genlmsg_end(skb, hdr);
	वापस 0;
पूर्ण

अटल पूर्णांक _smc_pnet_dump(काष्ठा net *net, काष्ठा sk_buff *skb, u32 portid,
			  u32 seq, u8 *pnetid, पूर्णांक start_idx)
अणु
	काष्ठा smc_pnettable *pnettable;
	काष्ठा smc_pnetentry *pnetelem;
	काष्ठा smc_net *sn;
	पूर्णांक idx = 0;

	/* get pnettable क्रम namespace */
	sn = net_generic(net, smc_net_id);
	pnettable = &sn->pnettable;

	/* dump pnettable entries */
	पढ़ो_lock(&pnettable->lock);
	list_क्रम_each_entry(pnetelem, &pnettable->pnetlist, list) अणु
		अगर (pnetid && !smc_pnet_match(pnetelem->pnet_name, pnetid))
			जारी;
		अगर (idx++ < start_idx)
			जारी;
		/* अगर this is not the initial namespace, dump only netdev */
		अगर (net != &init_net && pnetelem->type != SMC_PNET_ETH)
			जारी;
		अगर (smc_pnet_dumpinfo(skb, portid, seq, NLM_F_MULTI,
				      pnetelem)) अणु
			--idx;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&pnettable->lock);
	वापस idx;
पूर्ण

अटल पूर्णांक smc_pnet_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक idx;

	idx = _smc_pnet_dump(net, skb, NETLINK_CB(cb->skb).portid,
			     cb->nlh->nlmsg_seq, शून्य, cb->args[0]);

	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

/* Retrieve one PNETID entry */
अटल पूर्णांक smc_pnet_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	अगर (!info->attrs[SMC_PNETID_NAME])
		वापस -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	_smc_pnet_dump(net, msg, info->snd_portid, info->snd_seq,
		       nla_data(info->attrs[SMC_PNETID_NAME]), 0);

	/* finish multi part message and send it */
	hdr = nlmsg_put(msg, info->snd_portid, info->snd_seq, NLMSG_DONE, 0,
			NLM_F_MULTI);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस -EMSGSIZE;
	पूर्ण
	वापस genlmsg_reply(msg, info);
पूर्ण

/* Remove and delete all pnetids from pnet table.
 */
अटल पूर्णांक smc_pnet_flush(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);

	smc_pnet_हटाओ_by_pnetid(net, शून्य);
	वापस 0;
पूर्ण

/* SMC_PNETID generic netlink operation definition */
अटल स्थिर काष्ठा genl_ops smc_pnet_ops[] = अणु
	अणु
		.cmd = SMC_PNETID_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		/* can be retrieved by unprivileged users */
		.करोit = smc_pnet_get,
		.dumpit = smc_pnet_dump,
		.start = smc_pnet_dump_start
	पूर्ण,
	अणु
		.cmd = SMC_PNETID_ADD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.करोit = smc_pnet_add
	पूर्ण,
	अणु
		.cmd = SMC_PNETID_DEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.करोit = smc_pnet_del
	पूर्ण,
	अणु
		.cmd = SMC_PNETID_FLUSH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.करोit = smc_pnet_flush
	पूर्ण
पूर्ण;

/* SMC_PNETID family definition */
अटल काष्ठा genl_family smc_pnet_nl_family __ro_after_init = अणु
	.hdrsize = 0,
	.name = SMCR_GENL_FAMILY_NAME,
	.version = SMCR_GENL_FAMILY_VERSION,
	.maxattr = SMC_PNETID_MAX,
	.policy = smc_pnet_policy,
	.netnsok = true,
	.module = THIS_MODULE,
	.ops = smc_pnet_ops,
	.n_ops =  ARRAY_SIZE(smc_pnet_ops)
पूर्ण;

bool smc_pnet_is_ndev_pnetid(काष्ठा net *net, u8 *pnetid)
अणु
	काष्ठा smc_net *sn = net_generic(net, smc_net_id);
	काष्ठा smc_pnetids_ndev_entry *pe;
	bool rc = false;

	पढ़ो_lock(&sn->pnetids_ndev.lock);
	list_क्रम_each_entry(pe, &sn->pnetids_ndev.list, list) अणु
		अगर (smc_pnet_match(pnetid, pe->pnetid)) अणु
			rc = true;
			जाओ unlock;
		पूर्ण
	पूर्ण

unlock:
	पढ़ो_unlock(&sn->pnetids_ndev.lock);
	वापस rc;
पूर्ण

अटल पूर्णांक smc_pnet_add_pnetid(काष्ठा net *net, u8 *pnetid)
अणु
	काष्ठा smc_net *sn = net_generic(net, smc_net_id);
	काष्ठा smc_pnetids_ndev_entry *pe, *pi;

	pe = kzalloc(माप(*pe), GFP_KERNEL);
	अगर (!pe)
		वापस -ENOMEM;

	ग_लिखो_lock(&sn->pnetids_ndev.lock);
	list_क्रम_each_entry(pi, &sn->pnetids_ndev.list, list) अणु
		अगर (smc_pnet_match(pnetid, pe->pnetid)) अणु
			refcount_inc(&pi->refcnt);
			kमुक्त(pe);
			जाओ unlock;
		पूर्ण
	पूर्ण
	refcount_set(&pe->refcnt, 1);
	स_नकल(pe->pnetid, pnetid, SMC_MAX_PNETID_LEN);
	list_add_tail(&pe->list, &sn->pnetids_ndev.list);

unlock:
	ग_लिखो_unlock(&sn->pnetids_ndev.lock);
	वापस 0;
पूर्ण

अटल व्योम smc_pnet_हटाओ_pnetid(काष्ठा net *net, u8 *pnetid)
अणु
	काष्ठा smc_net *sn = net_generic(net, smc_net_id);
	काष्ठा smc_pnetids_ndev_entry *pe, *pe2;

	ग_लिखो_lock(&sn->pnetids_ndev.lock);
	list_क्रम_each_entry_safe(pe, pe2, &sn->pnetids_ndev.list, list) अणु
		अगर (smc_pnet_match(pnetid, pe->pnetid)) अणु
			अगर (refcount_dec_and_test(&pe->refcnt)) अणु
				list_del(&pe->list);
				kमुक्त(pe);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&sn->pnetids_ndev.lock);
पूर्ण

अटल व्योम smc_pnet_add_base_pnetid(काष्ठा net *net, काष्ठा net_device *dev,
				     u8 *ndev_pnetid)
अणु
	काष्ठा net_device *base_dev;

	base_dev = __pnet_find_base_ndev(dev);
	अगर (base_dev->flags & IFF_UP &&
	    !smc_pnetid_by_dev_port(base_dev->dev.parent, base_dev->dev_port,
				    ndev_pnetid)) अणु
		/* add to PNETIDs list */
		smc_pnet_add_pnetid(net, ndev_pnetid);
	पूर्ण
पूर्ण

/* create initial list of netdevice pnetids */
अटल व्योम smc_pnet_create_pnetids_list(काष्ठा net *net)
अणु
	u8 ndev_pnetid[SMC_MAX_PNETID_LEN];
	काष्ठा net_device *dev;

	rtnl_lock();
	क्रम_each_netdev(net, dev)
		smc_pnet_add_base_pnetid(net, dev, ndev_pnetid);
	rtnl_unlock();
पूर्ण

/* clean up list of netdevice pnetids */
अटल व्योम smc_pnet_destroy_pnetids_list(काष्ठा net *net)
अणु
	काष्ठा smc_net *sn = net_generic(net, smc_net_id);
	काष्ठा smc_pnetids_ndev_entry *pe, *temp_pe;

	ग_लिखो_lock(&sn->pnetids_ndev.lock);
	list_क्रम_each_entry_safe(pe, temp_pe, &sn->pnetids_ndev.list, list) अणु
		list_del(&pe->list);
		kमुक्त(pe);
	पूर्ण
	ग_लिखो_unlock(&sn->pnetids_ndev.lock);
पूर्ण

अटल पूर्णांक smc_pnet_netdev_event(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *event_dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(event_dev);
	u8 ndev_pnetid[SMC_MAX_PNETID_LEN];

	चयन (event) अणु
	हाल NETDEV_REBOOT:
	हाल NETDEV_UNREGISTER:
		smc_pnet_हटाओ_by_ndev(event_dev);
		smc_ib_ndev_change(event_dev, event);
		वापस NOTIFY_OK;
	हाल NETDEV_REGISTER:
		smc_pnet_add_by_ndev(event_dev);
		smc_ib_ndev_change(event_dev, event);
		वापस NOTIFY_OK;
	हाल NETDEV_UP:
		smc_pnet_add_base_pnetid(net, event_dev, ndev_pnetid);
		वापस NOTIFY_OK;
	हाल NETDEV_DOWN:
		event_dev = __pnet_find_base_ndev(event_dev);
		अगर (!smc_pnetid_by_dev_port(event_dev->dev.parent,
					    event_dev->dev_port, ndev_pnetid)) अणु
			/* हटाओ from PNETIDs list */
			smc_pnet_हटाओ_pnetid(net, ndev_pnetid);
		पूर्ण
		वापस NOTIFY_OK;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block smc_netdev_notअगरier = अणु
	.notअगरier_call = smc_pnet_netdev_event
पूर्ण;

/* init network namespace */
पूर्णांक smc_pnet_net_init(काष्ठा net *net)
अणु
	काष्ठा smc_net *sn = net_generic(net, smc_net_id);
	काष्ठा smc_pnettable *pnettable = &sn->pnettable;
	काष्ठा smc_pnetids_ndev *pnetids_ndev = &sn->pnetids_ndev;

	INIT_LIST_HEAD(&pnettable->pnetlist);
	rwlock_init(&pnettable->lock);
	INIT_LIST_HEAD(&pnetids_ndev->list);
	rwlock_init(&pnetids_ndev->lock);

	smc_pnet_create_pnetids_list(net);

	वापस 0;
पूर्ण

पूर्णांक __init smc_pnet_init(व्योम)
अणु
	पूर्णांक rc;

	rc = genl_रेजिस्टर_family(&smc_pnet_nl_family);
	अगर (rc)
		वापस rc;
	rc = रेजिस्टर_netdevice_notअगरier(&smc_netdev_notअगरier);
	अगर (rc)
		genl_unरेजिस्टर_family(&smc_pnet_nl_family);

	वापस rc;
पूर्ण

/* निकास network namespace */
व्योम smc_pnet_net_निकास(काष्ठा net *net)
अणु
	/* flush pnet table */
	smc_pnet_हटाओ_by_pnetid(net, शून्य);
	smc_pnet_destroy_pnetids_list(net);
पूर्ण

व्योम smc_pnet_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&smc_netdev_notअगरier);
	genl_unरेजिस्टर_family(&smc_pnet_nl_family);
पूर्ण

अटल काष्ठा net_device *__pnet_find_base_ndev(काष्ठा net_device *ndev)
अणु
	पूर्णांक i, nest_lvl;

	ASSERT_RTNL();
	nest_lvl = ndev->lower_level;
	क्रम (i = 0; i < nest_lvl; i++) अणु
		काष्ठा list_head *lower = &ndev->adj_list.lower;

		अगर (list_empty(lower))
			अवरोध;
		lower = lower->next;
		ndev = netdev_lower_get_next(ndev, &lower);
	पूर्ण
	वापस ndev;
पूर्ण

/* Determine one base device क्रम stacked net devices.
 * If the lower device level contains more than one devices
 * (क्रम instance with bonding slaves), just the first device
 * is used to reach a base device.
 */
अटल काष्ठा net_device *pnet_find_base_ndev(काष्ठा net_device *ndev)
अणु
	rtnl_lock();
	ndev = __pnet_find_base_ndev(ndev);
	rtnl_unlock();
	वापस ndev;
पूर्ण

अटल पूर्णांक smc_pnet_find_ndev_pnetid_by_table(काष्ठा net_device *ndev,
					      u8 *pnetid)
अणु
	काष्ठा smc_pnettable *pnettable;
	काष्ठा net *net = dev_net(ndev);
	काष्ठा smc_pnetentry *pnetelem;
	काष्ठा smc_net *sn;
	पूर्णांक rc = -ENOENT;

	/* get pnettable क्रम namespace */
	sn = net_generic(net, smc_net_id);
	pnettable = &sn->pnettable;

	पढ़ो_lock(&pnettable->lock);
	list_क्रम_each_entry(pnetelem, &pnettable->pnetlist, list) अणु
		अगर (pnetelem->type == SMC_PNET_ETH && ndev == pnetelem->ndev) अणु
			/* get pnetid of netdev device */
			स_नकल(pnetid, pnetelem->pnet_name, SMC_MAX_PNETID_LEN);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&pnettable->lock);
	वापस rc;
पूर्ण

/* find a roce device क्रम the given pnetid */
अटल व्योम _smc_pnet_find_roce_by_pnetid(u8 *pnet_id,
					  काष्ठा smc_init_info *ini,
					  काष्ठा smc_ib_device *known_dev)
अणु
	काष्ठा smc_ib_device *ibdev;
	पूर्णांक i;

	ini->ib_dev = शून्य;
	mutex_lock(&smc_ib_devices.mutex);
	list_क्रम_each_entry(ibdev, &smc_ib_devices.list, list) अणु
		अगर (ibdev == known_dev)
			जारी;
		क्रम (i = 1; i <= SMC_MAX_PORTS; i++) अणु
			अगर (!rdma_is_port_valid(ibdev->ibdev, i))
				जारी;
			अगर (smc_pnet_match(ibdev->pnetid[i - 1], pnet_id) &&
			    smc_ib_port_active(ibdev, i) &&
			    !test_bit(i - 1, ibdev->ports_going_away) &&
			    !smc_ib_determine_gid(ibdev, i, ini->vlan_id,
						  ini->ib_gid, शून्य)) अणु
				ini->ib_dev = ibdev;
				ini->ib_port = i;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&smc_ib_devices.mutex);
पूर्ण

/* find alternate roce device with same pnet_id and vlan_id */
व्योम smc_pnet_find_alt_roce(काष्ठा smc_link_group *lgr,
			    काष्ठा smc_init_info *ini,
			    काष्ठा smc_ib_device *known_dev)
अणु
	_smc_pnet_find_roce_by_pnetid(lgr->pnet_id, ini, known_dev);
पूर्ण

/* अगर handshake network device beदीर्घs to a roce device, वापस its
 * IB device and port
 */
अटल व्योम smc_pnet_find_rdma_dev(काष्ठा net_device *netdev,
				   काष्ठा smc_init_info *ini)
अणु
	काष्ठा smc_ib_device *ibdev;

	mutex_lock(&smc_ib_devices.mutex);
	list_क्रम_each_entry(ibdev, &smc_ib_devices.list, list) अणु
		काष्ठा net_device *ndev;
		पूर्णांक i;

		क्रम (i = 1; i <= SMC_MAX_PORTS; i++) अणु
			अगर (!rdma_is_port_valid(ibdev->ibdev, i))
				जारी;
			अगर (!ibdev->ibdev->ops.get_netdev)
				जारी;
			ndev = ibdev->ibdev->ops.get_netdev(ibdev->ibdev, i);
			अगर (!ndev)
				जारी;
			dev_put(ndev);
			अगर (netdev == ndev &&
			    smc_ib_port_active(ibdev, i) &&
			    !test_bit(i - 1, ibdev->ports_going_away) &&
			    !smc_ib_determine_gid(ibdev, i, ini->vlan_id,
						  ini->ib_gid, शून्य)) अणु
				ini->ib_dev = ibdev;
				ini->ib_port = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&smc_ib_devices.mutex);
पूर्ण

/* Determine the corresponding IB device port based on the hardware PNETID.
 * Searching stops at the first matching active IB device port with vlan_id
 * configured.
 * If nothing found, check pnetid table.
 * If nothing found, try to use handshake device
 */
अटल व्योम smc_pnet_find_roce_by_pnetid(काष्ठा net_device *ndev,
					 काष्ठा smc_init_info *ini)
अणु
	u8 ndev_pnetid[SMC_MAX_PNETID_LEN];

	ndev = pnet_find_base_ndev(ndev);
	अगर (smc_pnetid_by_dev_port(ndev->dev.parent, ndev->dev_port,
				   ndev_pnetid) &&
	    smc_pnet_find_ndev_pnetid_by_table(ndev, ndev_pnetid)) अणु
		smc_pnet_find_rdma_dev(ndev, ini);
		वापस; /* pnetid could not be determined */
	पूर्ण
	_smc_pnet_find_roce_by_pnetid(ndev_pnetid, ini, शून्य);
पूर्ण

अटल व्योम smc_pnet_find_ism_by_pnetid(काष्ठा net_device *ndev,
					काष्ठा smc_init_info *ini)
अणु
	u8 ndev_pnetid[SMC_MAX_PNETID_LEN];
	काष्ठा smcd_dev *ismdev;

	ndev = pnet_find_base_ndev(ndev);
	अगर (smc_pnetid_by_dev_port(ndev->dev.parent, ndev->dev_port,
				   ndev_pnetid) &&
	    smc_pnet_find_ndev_pnetid_by_table(ndev, ndev_pnetid))
		वापस; /* pnetid could not be determined */

	mutex_lock(&smcd_dev_list.mutex);
	list_क्रम_each_entry(ismdev, &smcd_dev_list.list, list) अणु
		अगर (smc_pnet_match(ismdev->pnetid, ndev_pnetid) &&
		    !ismdev->going_away &&
		    (!ini->ism_peer_gid[0] ||
		     !smc_ism_cantalk(ini->ism_peer_gid[0], ini->vlan_id,
				      ismdev))) अणु
			ini->ism_dev[0] = ismdev;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&smcd_dev_list.mutex);
पूर्ण

/* PNET table analysis क्रम a given sock:
 * determine ib_device and port beदीर्घing to used पूर्णांकernal TCP socket
 * ethernet पूर्णांकerface.
 */
व्योम smc_pnet_find_roce_resource(काष्ठा sock *sk, काष्ठा smc_init_info *ini)
अणु
	काष्ठा dst_entry *dst = sk_dst_get(sk);

	ini->ib_dev = शून्य;
	ini->ib_port = 0;
	अगर (!dst)
		जाओ out;
	अगर (!dst->dev)
		जाओ out_rel;

	smc_pnet_find_roce_by_pnetid(dst->dev, ini);

out_rel:
	dst_release(dst);
out:
	वापस;
पूर्ण

व्योम smc_pnet_find_ism_resource(काष्ठा sock *sk, काष्ठा smc_init_info *ini)
अणु
	काष्ठा dst_entry *dst = sk_dst_get(sk);

	ini->ism_dev[0] = शून्य;
	अगर (!dst)
		जाओ out;
	अगर (!dst->dev)
		जाओ out_rel;

	smc_pnet_find_ism_by_pnetid(dst->dev, ini);

out_rel:
	dst_release(dst);
out:
	वापस;
पूर्ण

/* Lookup and apply a pnet table entry to the given ib device.
 */
पूर्णांक smc_pnetid_by_table_ib(काष्ठा smc_ib_device *smcibdev, u8 ib_port)
अणु
	अक्षर *ib_name = smcibdev->ibdev->name;
	काष्ठा smc_pnettable *pnettable;
	काष्ठा smc_pnetentry *पंचांगp_pe;
	काष्ठा smc_net *sn;
	पूर्णांक rc = -ENOENT;

	/* get pnettable क्रम init namespace */
	sn = net_generic(&init_net, smc_net_id);
	pnettable = &sn->pnettable;

	पढ़ो_lock(&pnettable->lock);
	list_क्रम_each_entry(पंचांगp_pe, &pnettable->pnetlist, list) अणु
		अगर (पंचांगp_pe->type == SMC_PNET_IB &&
		    !म_भेदन(पंचांगp_pe->ib_name, ib_name, IB_DEVICE_NAME_MAX) &&
		    पंचांगp_pe->ib_port == ib_port) अणु
			smc_pnet_apply_ib(smcibdev, ib_port, पंचांगp_pe->pnet_name);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&pnettable->lock);

	वापस rc;
पूर्ण

/* Lookup and apply a pnet table entry to the given smcd device.
 */
पूर्णांक smc_pnetid_by_table_smcd(काष्ठा smcd_dev *smcddev)
अणु
	स्थिर अक्षर *ib_name = dev_name(&smcddev->dev);
	काष्ठा smc_pnettable *pnettable;
	काष्ठा smc_pnetentry *पंचांगp_pe;
	काष्ठा smc_net *sn;
	पूर्णांक rc = -ENOENT;

	/* get pnettable क्रम init namespace */
	sn = net_generic(&init_net, smc_net_id);
	pnettable = &sn->pnettable;

	पढ़ो_lock(&pnettable->lock);
	list_क्रम_each_entry(पंचांगp_pe, &pnettable->pnetlist, list) अणु
		अगर (पंचांगp_pe->type == SMC_PNET_IB &&
		    !म_भेदन(पंचांगp_pe->ib_name, ib_name, IB_DEVICE_NAME_MAX)) अणु
			smc_pnet_apply_smcd(smcddev, पंचांगp_pe->pnet_name);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&pnettable->lock);

	वापस rc;
पूर्ण
