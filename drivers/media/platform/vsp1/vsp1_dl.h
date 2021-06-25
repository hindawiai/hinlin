<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_dl.h  --  R-Car VSP1 Display List
 *
 * Copyright (C) 2015 Renesas Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_DL_H__
#घोषणा __VSP1_DL_H__

#समावेश <linux/types.h>

काष्ठा vsp1_device;
काष्ठा vsp1_dl_body;
काष्ठा vsp1_dl_body_pool;
काष्ठा vsp1_dl_list;
काष्ठा vsp1_dl_manager;

/* Keep these flags in sync with VSP1_DU_STATUS_* in include/media/vsp1.h. */
#घोषणा VSP1_DL_FRAME_END_COMPLETED		BIT(0)
#घोषणा VSP1_DL_FRAME_END_WRITEBACK		BIT(1)
#घोषणा VSP1_DL_FRAME_END_INTERNAL		BIT(2)

/**
 * काष्ठा vsp1_dl_ext_cmd - Extended Display command
 * @pool: pool to which this command beदीर्घs
 * @मुक्त: entry in the pool of मुक्त commands list
 * @opcode: command type opcode
 * @flags: flags used by the command
 * @cmds: array of command bodies क्रम this extended cmd
 * @num_cmds: quantity of commands in @cmds array
 * @cmd_dma: DMA address of the command body
 * @data: memory allocation क्रम command-specअगरic data
 * @data_dma: DMA address क्रम command-specअगरic data
 */
काष्ठा vsp1_dl_ext_cmd अणु
	काष्ठा vsp1_dl_cmd_pool *pool;
	काष्ठा list_head मुक्त;

	u8 opcode;
	u32 flags;

	काष्ठा vsp1_pre_ext_dl_body *cmds;
	अचिन्हित पूर्णांक num_cmds;
	dma_addr_t cmd_dma;

	व्योम *data;
	dma_addr_t data_dma;
पूर्ण;

व्योम vsp1_dlm_setup(काष्ठा vsp1_device *vsp1);

काष्ठा vsp1_dl_manager *vsp1_dlm_create(काष्ठा vsp1_device *vsp1,
					अचिन्हित पूर्णांक index,
					अचिन्हित पूर्णांक pपुनः_स्मृति);
व्योम vsp1_dlm_destroy(काष्ठा vsp1_dl_manager *dlm);
व्योम vsp1_dlm_reset(काष्ठा vsp1_dl_manager *dlm);
अचिन्हित पूर्णांक vsp1_dlm_irq_frame_end(काष्ठा vsp1_dl_manager *dlm);
काष्ठा vsp1_dl_body *vsp1_dlm_dl_body_get(काष्ठा vsp1_dl_manager *dlm);

काष्ठा vsp1_dl_list *vsp1_dl_list_get(काष्ठा vsp1_dl_manager *dlm);
व्योम vsp1_dl_list_put(काष्ठा vsp1_dl_list *dl);
काष्ठा vsp1_dl_body *vsp1_dl_list_get_body0(काष्ठा vsp1_dl_list *dl);
काष्ठा vsp1_dl_ext_cmd *vsp1_dl_get_pre_cmd(काष्ठा vsp1_dl_list *dl);
व्योम vsp1_dl_list_commit(काष्ठा vsp1_dl_list *dl, अचिन्हित पूर्णांक dl_flags);

काष्ठा vsp1_dl_body_pool *
vsp1_dl_body_pool_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक num_bodies,
			 अचिन्हित पूर्णांक num_entries, माप_प्रकार extra_size);
व्योम vsp1_dl_body_pool_destroy(काष्ठा vsp1_dl_body_pool *pool);
काष्ठा vsp1_dl_body *vsp1_dl_body_get(काष्ठा vsp1_dl_body_pool *pool);
व्योम vsp1_dl_body_put(काष्ठा vsp1_dl_body *dlb);

व्योम vsp1_dl_body_ग_लिखो(काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data);
पूर्णांक vsp1_dl_list_add_body(काष्ठा vsp1_dl_list *dl, काष्ठा vsp1_dl_body *dlb);
पूर्णांक vsp1_dl_list_add_chain(काष्ठा vsp1_dl_list *head, काष्ठा vsp1_dl_list *dl);

#पूर्ण_अगर /* __VSP1_DL_H__ */
