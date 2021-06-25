<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SCSI library functions depending on DMA
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

/**
 * scsi_dma_map - perक्रमm DMA mapping against command's sg lists
 * @cmd:	scsi command
 *
 * Returns the number of sg lists actually used, zero अगर the sg lists
 * is शून्य, or -ENOMEM अगर the mapping failed.
 */
पूर्णांक scsi_dma_map(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक nseg = 0;

	अगर (scsi_sg_count(cmd)) अणु
		काष्ठा device *dev = cmd->device->host->dma_dev;

		nseg = dma_map_sg(dev, scsi_sglist(cmd), scsi_sg_count(cmd),
				  cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			वापस -ENOMEM;
	पूर्ण
	वापस nseg;
पूर्ण
EXPORT_SYMBOL(scsi_dma_map);

/**
 * scsi_dma_unmap - unmap command's sg lists mapped by scsi_dma_map
 * @cmd:	scsi command
 */
व्योम scsi_dma_unmap(काष्ठा scsi_cmnd *cmd)
अणु
	अगर (scsi_sg_count(cmd)) अणु
		काष्ठा device *dev = cmd->device->host->dma_dev;

		dma_unmap_sg(dev, scsi_sglist(cmd), scsi_sg_count(cmd),
			     cmd->sc_data_direction);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(scsi_dma_unmap);
