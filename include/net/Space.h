<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* A unअगरied ethernet device probe.  This is the easiest way to have every
 * ethernet adaptor have the name "eth[0123...]".
 */

काष्ठा net_device *hp100_probe(पूर्णांक unit);
काष्ठा net_device *ultra_probe(पूर्णांक unit);
काष्ठा net_device *wd_probe(पूर्णांक unit);
काष्ठा net_device *ne_probe(पूर्णांक unit);
काष्ठा net_device *fmv18x_probe(पूर्णांक unit);
काष्ठा net_device *i82596_probe(पूर्णांक unit);
काष्ठा net_device *ni65_probe(पूर्णांक unit);
काष्ठा net_device *sonic_probe(पूर्णांक unit);
काष्ठा net_device *smc_init(पूर्णांक unit);
काष्ठा net_device *atarilance_probe(पूर्णांक unit);
काष्ठा net_device *sun3lance_probe(पूर्णांक unit);
काष्ठा net_device *sun3_82586_probe(पूर्णांक unit);
काष्ठा net_device *apne_probe(पूर्णांक unit);
काष्ठा net_device *cs89x0_probe(पूर्णांक unit);
काष्ठा net_device *mvme147lance_probe(पूर्णांक unit);
काष्ठा net_device *tc515_probe(पूर्णांक unit);
काष्ठा net_device *lance_probe(पूर्णांक unit);
काष्ठा net_device *cops_probe(पूर्णांक unit);
काष्ठा net_device *ltpc_probe(व्योम);

/* Fibre Channel adapters */
पूर्णांक iph5526_probe(काष्ठा net_device *dev);

/* SBNI adapters */
पूर्णांक sbni_probe(पूर्णांक unit);
