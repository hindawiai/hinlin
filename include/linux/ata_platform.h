<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_ATA_PLATFORM_H
#घोषणा __LINUX_ATA_PLATFORM_H

काष्ठा pata_platक्रमm_info अणु
	/*
	 * I/O port shअगरt, क्रम platक्रमms with ports that are
	 * स्थिरantly spaced and need larger than the 1-byte
	 * spacing used by ata_std_ports().
	 */
	अचिन्हित पूर्णांक ioport_shअगरt;
पूर्ण;

काष्ठा scsi_host_ढाँचा;

बाह्य पूर्णांक __pata_platक्रमm_probe(काष्ठा device *dev,
				 काष्ठा resource *io_res,
				 काष्ठा resource *ctl_res,
				 काष्ठा resource *irq_res,
				 अचिन्हित पूर्णांक ioport_shअगरt,
				 पूर्णांक __pio_mask,
				 काष्ठा scsi_host_ढाँचा *sht,
				 bool use16bit);

/*
 * Marvell SATA निजी data
 */
काष्ठा mv_sata_platक्रमm_data अणु
	पूर्णांक	n_ports; /* number of sata ports */
पूर्ण;

#पूर्ण_अगर /* __LINUX_ATA_PLATFORM_H */
