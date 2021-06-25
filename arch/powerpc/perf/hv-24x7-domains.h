<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * DOMAIN(name, num, index_kind, is_physical)
 *
 * @name:	An all caps token, suitable क्रम use in generating an क्रमागत
 *		member and appending to an event name in sysfs.
 *
 * @num:	The number corresponding to the करोमुख्य as given in
 *		करोcumentation. We assume the catalog करोमुख्य and the hcall
 *		करोमुख्य have the same numbering (so far they करो), but this
 *		may need to be changed in the future.
 *
 * @index_kind: A stringअगरiable token describing the meaning of the index
 *		within the given करोमुख्य. Must fit the parsing rules of the
 *		perf sysfs api.
 *
 * @is_physical: True अगर the करोमुख्य is physical, false otherwise (अगर भव).
 *
 * Note: The terms PHYS_CHIP, PHYS_CORE, VCPU correspond to physical chip,
 *	 physical core and भव processor in 24x7 Counters specअगरications.
 */

DOMAIN(PHYS_CHIP, 0x01, chip, true)
DOMAIN(PHYS_CORE, 0x02, core, true)
DOMAIN(VCPU_HOME_CORE, 0x03, vcpu, false)
DOMAIN(VCPU_HOME_CHIP, 0x04, vcpu, false)
DOMAIN(VCPU_HOME_NODE, 0x05, vcpu, false)
DOMAIN(VCPU_REMOTE_NODE, 0x06, vcpu, false)
