<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Description: EBTables 802.1Q match extension kernelspace module.
 * Authors: Nick Fedchik <nick@fedchik.org.ua>
 *          Bart De Schuymer <bdschuym@panकरोra.be>
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_vlan.h>

#घोषणा MODULE_VERS "0.6"

MODULE_AUTHOR("Nick Fedchik <nick@fedchik.org.ua>");
MODULE_DESCRIPTION("Ebtables: 802.1Q VLAN tag match");
MODULE_LICENSE("GPL");

#घोषणा GET_BITMASK(_BIT_MASK_) info->biपंचांगask & _BIT_MASK_
#घोषणा EXIT_ON_MISMATCH(_MATCH_,_MASK_) अणुअगर (!((info->_MATCH_ == _MATCH_)^!!(info->invflags & _MASK_))) वापस false; पूर्ण

अटल bool
ebt_vlan_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_vlan_info *info = par->matchinfo;

	अचिन्हित लघु TCI;	/* Whole TCI, given from parsed frame */
	अचिन्हित लघु id;	/* VLAN ID, given from frame TCI */
	अचिन्हित अक्षर prio;	/* user_priority, given from frame TCI */
	/* VLAN encapsulated Type/Length field, given from orig frame */
	__be16 encap;

	अगर (skb_vlan_tag_present(skb)) अणु
		TCI = skb_vlan_tag_get(skb);
		encap = skb->protocol;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा vlan_hdr *fp;
		काष्ठा vlan_hdr _frame;

		fp = skb_header_poपूर्णांकer(skb, 0, माप(_frame), &_frame);
		अगर (fp == शून्य)
			वापस false;

		TCI = ntohs(fp->h_vlan_TCI);
		encap = fp->h_vlan_encapsulated_proto;
	पूर्ण

	/* Tag Control Inक्रमmation (TCI) consists of the following elements:
	 * - User_priority. The user_priority field is three bits in length,
	 * पूर्णांकerpreted as a binary number.
	 * - Canonical Format Indicator (CFI). The Canonical Format Indicator
	 * (CFI) is a single bit flag value. Currently ignored.
	 * - VLAN Identअगरier (VID). The VID is encoded as
	 * an अचिन्हित binary number.
	 */
	id = TCI & VLAN_VID_MASK;
	prio = (TCI >> 13) & 0x7;

	/* Checking VLAN Identअगरier (VID) */
	अगर (GET_BITMASK(EBT_VLAN_ID))
		EXIT_ON_MISMATCH(id, EBT_VLAN_ID);

	/* Checking user_priority */
	अगर (GET_BITMASK(EBT_VLAN_PRIO))
		EXIT_ON_MISMATCH(prio, EBT_VLAN_PRIO);

	/* Checking Encapsulated Proto (Length/Type) field */
	अगर (GET_BITMASK(EBT_VLAN_ENCAP))
		EXIT_ON_MISMATCH(encap, EBT_VLAN_ENCAP);

	वापस true;
पूर्ण

अटल पूर्णांक ebt_vlan_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा ebt_vlan_info *info = par->matchinfo;
	स्थिर काष्ठा ebt_entry *e = par->entryinfo;

	/* Is it 802.1Q frame checked? */
	अगर (e->ethproto != htons(ETH_P_8021Q)) अणु
		pr_debug("passed entry proto %2.4X is not 802.1Q (8100)\n",
			 ntohs(e->ethproto));
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम biपंचांगask range
	 * True अगर even one bit is out of mask
	 */
	अगर (info->biपंचांगask & ~EBT_VLAN_MASK) अणु
		pr_debug("bitmask %2X is out of mask (%2X)\n",
			 info->biपंचांगask, EBT_VLAN_MASK);
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम inversion flags range */
	अगर (info->invflags & ~EBT_VLAN_MASK) अणु
		pr_debug("inversion flags %2X is out of mask (%2X)\n",
			 info->invflags, EBT_VLAN_MASK);
		वापस -EINVAL;
	पूर्ण

	/* Reserved VLAN ID (VID) values
	 * -----------------------------
	 * 0 - The null VLAN ID.
	 * 1 - The शेष Port VID (PVID)
	 * 0x0FFF - Reserved क्रम implementation use.
	 * अगर_vlan.h: VLAN_N_VID 4096.
	 */
	अगर (GET_BITMASK(EBT_VLAN_ID)) अणु
		अगर (!!info->id) अणु /* अगर id!=0 => check vid range */
			अगर (info->id > VLAN_N_VID) अणु
				pr_debug("id %d is out of range (1-4096)\n",
					 info->id);
				वापस -EINVAL;
			पूर्ण
			/* Note: This is valid VLAN-tagged frame poपूर्णांक.
			 * Any value of user_priority are acceptable,
			 * but should be ignored according to 802.1Q Std.
			 * So we just drop the prio flag.
			 */
			info->biपंचांगask &= ~EBT_VLAN_PRIO;
		पूर्ण
		/* Else, id=0 (null VLAN ID)  => user_priority range (any?) */
	पूर्ण

	अगर (GET_BITMASK(EBT_VLAN_PRIO)) अणु
		अगर ((अचिन्हित अक्षर) info->prio > 7) अणु
			pr_debug("prio %d is out of range (0-7)\n",
				 info->prio);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* Check क्रम encapsulated proto range - it is possible to be
	 * any value क्रम u_लघु range.
	 * अगर_ether.h:  ETH_ZLEN        60   -  Min. octets in frame sans FCS
	 */
	अगर (GET_BITMASK(EBT_VLAN_ENCAP)) अणु
		अगर ((अचिन्हित लघु) ntohs(info->encap) < ETH_ZLEN) अणु
			pr_debug("encap frame length %d is less than "
				 "minimal\n", ntohs(info->encap));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match ebt_vlan_mt_reg __पढ़ो_mostly = अणु
	.name		= "vlan",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_vlan_mt,
	.checkentry	= ebt_vlan_mt_check,
	.matchsize	= माप(काष्ठा ebt_vlan_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_vlan_init(व्योम)
अणु
	pr_debug("ebtables 802.1Q extension module v" MODULE_VERS "\n");
	वापस xt_रेजिस्टर_match(&ebt_vlan_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_vlan_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_vlan_mt_reg);
पूर्ण

module_init(ebt_vlan_init);
module_निकास(ebt_vlan_fini);
