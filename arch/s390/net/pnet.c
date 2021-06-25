<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  IBM System z PNET ID Support
 *
 *    Copyright IBM Corp. 2018
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/ccwgroup.h>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/pnet.h>
#समावेश <यंत्र/ebcdic.h>

#घोषणा PNETIDS_LEN		64	/* Total utility string length in bytes
					 * to cover up to 4 PNETIDs of 16 bytes
					 * क्रम up to 4 device ports
					 */
#घोषणा MAX_PNETID_LEN		16	/* Max.length of a single port PNETID */
#घोषणा MAX_PNETID_PORTS	(PNETIDS_LEN / MAX_PNETID_LEN)
					/* Max. # of ports with a PNETID */

/*
 * Get the PNETIDs from a device.
 * s390 hardware supports the definition of a so-called Physical Network
 * Identअगरier (लघु PNETID) per network device port. These PNETIDs can be
 * used to identअगरy network devices that are attached to the same physical
 * network (broadcast करोमुख्य).
 *
 * The device can be
 * - a ccwgroup device with all bundled subchannels having the same PNETID
 * - a PCI attached network device
 *
 * Returns:
 * 0:		PNETIDs extracted from device.
 * -ENOMEM:	No memory to extract utility string.
 * -EOPNOTSUPP: Device type without utility string support
 */
अटल पूर्णांक pnet_ids_by_device(काष्ठा device *dev, u8 *pnetids)
अणु
	स_रखो(pnetids, 0, PNETIDS_LEN);
	अगर (dev_is_ccwgroup(dev)) अणु
		काष्ठा ccwgroup_device *gdev = to_ccwgroupdev(dev);
		u8 *util_str;

		util_str = ccw_device_get_util_str(gdev->cdev[0], 0);
		अगर (!util_str)
			वापस -ENOMEM;
		स_नकल(pnetids, util_str, PNETIDS_LEN);
		EBCASC(pnetids, PNETIDS_LEN);
		kमुक्त(util_str);
		वापस 0;
	पूर्ण
	अगर (dev_is_pci(dev)) अणु
		काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));

		स_नकल(pnetids, zdev->util_str, माप(zdev->util_str));
		EBCASC(pnetids, माप(zdev->util_str));
		वापस 0;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

/*
 * Extract the pnetid क्रम a device port.
 *
 * Return 0 अगर a pnetid is found and -ENOENT otherwise.
 */
पूर्णांक pnet_id_by_dev_port(काष्ठा device *dev, अचिन्हित लघु port, u8 *pnetid)
अणु
	u8 pnetids[MAX_PNETID_PORTS][MAX_PNETID_LEN];
	अटल स्थिर u8 zero[MAX_PNETID_LEN] = अणु 0 पूर्ण;
	पूर्णांक rc = 0;

	अगर (!dev || port >= MAX_PNETID_PORTS)
		वापस -ENOENT;

	अगर (!pnet_ids_by_device(dev, (u8 *)pnetids) &&
	    स_भेद(pnetids[port], zero, MAX_PNETID_LEN))
		स_नकल(pnetid, pnetids[port], MAX_PNETID_LEN);
	अन्यथा
		rc = -ENOENT;

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pnet_id_by_dev_port);

MODULE_DESCRIPTION("pnetid determination from utility strings");
MODULE_LICENSE("GPL");
