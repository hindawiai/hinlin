<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IDE_GD_H
#घोषणा __IDE_GD_H

#घोषणा DRV_NAME "ide-gd"
#घोषणा PFX DRV_NAME ": "

/* define to see debug info */
#घोषणा IDE_GD_DEBUG_LOG	0

#अगर IDE_GD_DEBUG_LOG
#घोषणा ide_debug_log(lvl, fmt, args...) __ide_debug_log(lvl, fmt, ## args)
#अन्यथा
#घोषणा ide_debug_log(lvl, fmt, args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा ide_disk_obj अणु
	ide_drive_t		*drive;
	काष्ठा ide_driver	*driver;
	काष्ठा gendisk		*disk;
	काष्ठा device		dev;
	अचिन्हित पूर्णांक		खोलोers;	/* रक्षित by BKL क्रम now */

	/* used क्रम blk_अणुfs,pcपूर्ण_request() requests */
	काष्ठा ide_atapi_pc queued_pc;

	/* Last error inक्रमmation */
	u8 sense_key, asc, ascq;

	पूर्णांक progress_indication;

	/* Device inक्रमmation */
	/* Current क्रमmat */
	पूर्णांक blocks, block_size, bs_factor;
	/* Last क्रमmat capacity descriptor */
	u8 cap_desc[8];
	/* Copy of the flexible disk page */
	u8 flexible_disk_page[32];
पूर्ण;

sector_t ide_gd_capacity(ide_drive_t *);

#पूर्ण_अगर /* __IDE_GD_H */
