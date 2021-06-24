<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_BACKEND_H
#घोषणा TARGET_CORE_BACKEND_H

#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <target/target_core_base.h>

#घोषणा TRANSPORT_FLAG_PASSTHROUGH		0x1
/*
 * ALUA commands, state checks and setup operations are handled by the
 * backend module.
 */
#घोषणा TRANSPORT_FLAG_PASSTHROUGH_ALUA		0x2
#घोषणा TRANSPORT_FLAG_PASSTHROUGH_PGR          0x4

काष्ठा request_queue;
काष्ठा scatterlist;

काष्ठा target_backend_ops अणु
	अक्षर name[16];
	अक्षर inquiry_prod[16];
	अक्षर inquiry_rev[4];
	काष्ठा module *owner;

	u8 transport_flags_शेष;
	u8 transport_flags_changeable;

	पूर्णांक (*attach_hba)(काष्ठा se_hba *, u32);
	व्योम (*detach_hba)(काष्ठा se_hba *);
	पूर्णांक (*pmode_enable_hba)(काष्ठा se_hba *, अचिन्हित दीर्घ);

	काष्ठा se_device *(*alloc_device)(काष्ठा se_hba *, स्थिर अक्षर *);
	पूर्णांक (*configure_device)(काष्ठा se_device *);
	व्योम (*destroy_device)(काष्ठा se_device *);
	व्योम (*मुक्त_device)(काष्ठा se_device *device);
	काष्ठा se_dev_plug *(*plug_device)(काष्ठा se_device *se_dev);
	व्योम (*unplug_device)(काष्ठा se_dev_plug *se_plug);

	sमाप_प्रकार (*set_configfs_dev_params)(काष्ठा se_device *,
					   स्थिर अक्षर *, sमाप_प्रकार);
	sमाप_प्रकार (*show_configfs_dev_params)(काष्ठा se_device *, अक्षर *);

	sense_reason_t (*parse_cdb)(काष्ठा se_cmd *cmd);
	व्योम (*पंचांगr_notअगरy)(काष्ठा se_device *se_dev, क्रमागत tcm_पंचांगreq_table,
			   काष्ठा list_head *पातed_cmds);
	u32 (*get_device_type)(काष्ठा se_device *);
	sector_t (*get_blocks)(काष्ठा se_device *);
	sector_t (*get_alignment_offset_lbas)(काष्ठा se_device *);
	/* lbppbe = logical blocks per physical block exponent. see SBC-3 */
	अचिन्हित पूर्णांक (*get_lbppbe)(काष्ठा se_device *);
	अचिन्हित पूर्णांक (*get_io_min)(काष्ठा se_device *);
	अचिन्हित पूर्णांक (*get_io_opt)(काष्ठा se_device *);
	अचिन्हित अक्षर *(*get_sense_buffer)(काष्ठा se_cmd *);
	bool (*get_ग_लिखो_cache)(काष्ठा se_device *);
	पूर्णांक (*init_prot)(काष्ठा se_device *);
	पूर्णांक (*क्रमmat_prot)(काष्ठा se_device *);
	व्योम (*मुक्त_prot)(काष्ठा se_device *);

	काष्ठा configfs_attribute **tb_dev_attrib_attrs;
	काष्ठा configfs_attribute **tb_dev_action_attrs;
पूर्ण;

काष्ठा sbc_ops अणु
	sense_reason_t (*execute_rw)(काष्ठा se_cmd *cmd, काष्ठा scatterlist *,
				     u32, क्रमागत dma_data_direction);
	sense_reason_t (*execute_sync_cache)(काष्ठा se_cmd *cmd);
	sense_reason_t (*execute_ग_लिखो_same)(काष्ठा se_cmd *cmd);
	sense_reason_t (*execute_unmap)(काष्ठा se_cmd *cmd,
				sector_t lba, sector_t nolb);
पूर्ण;

पूर्णांक	transport_backend_रेजिस्टर(स्थिर काष्ठा target_backend_ops *);
व्योम	target_backend_unरेजिस्टर(स्थिर काष्ठा target_backend_ops *);

व्योम	target_complete_cmd(काष्ठा se_cmd *, u8);
व्योम	target_set_cmd_data_length(काष्ठा se_cmd *, पूर्णांक);
व्योम	target_complete_cmd_with_length(काष्ठा se_cmd *, u8, पूर्णांक);

व्योम	transport_copy_sense_to_cmd(काष्ठा se_cmd *, अचिन्हित अक्षर *);

sense_reason_t	spc_parse_cdb(काष्ठा se_cmd *cmd, अचिन्हित पूर्णांक *size);
sense_reason_t	spc_emulate_report_luns(काष्ठा se_cmd *cmd);
sense_reason_t	spc_emulate_inquiry_std(काष्ठा se_cmd *, अचिन्हित अक्षर *);
sense_reason_t	spc_emulate_evpd_83(काष्ठा se_cmd *, अचिन्हित अक्षर *);

sense_reason_t	sbc_parse_cdb(काष्ठा se_cmd *cmd, काष्ठा sbc_ops *ops);
u32	sbc_get_device_rev(काष्ठा se_device *dev);
u32	sbc_get_device_type(काष्ठा se_device *dev);
sector_t	sbc_get_ग_लिखो_same_sectors(काष्ठा se_cmd *cmd);
व्योम	sbc_dअगर_generate(काष्ठा se_cmd *);
sense_reason_t	sbc_dअगर_verअगरy(काष्ठा se_cmd *, sector_t, अचिन्हित पूर्णांक,
				     अचिन्हित पूर्णांक, काष्ठा scatterlist *, पूर्णांक);
व्योम sbc_dअगर_copy_prot(काष्ठा se_cmd *, अचिन्हित पूर्णांक, bool,
		       काष्ठा scatterlist *, पूर्णांक);
व्योम	transport_set_vpd_proto_id(काष्ठा t10_vpd *, अचिन्हित अक्षर *);
पूर्णांक	transport_set_vpd_assoc(काष्ठा t10_vpd *, अचिन्हित अक्षर *);
पूर्णांक	transport_set_vpd_ident_type(काष्ठा t10_vpd *, अचिन्हित अक्षर *);
पूर्णांक	transport_set_vpd_ident(काष्ठा t10_vpd *, अचिन्हित अक्षर *);

बाह्य काष्ठा configfs_attribute *sbc_attrib_attrs[];
बाह्य काष्ठा configfs_attribute *passthrough_attrib_attrs[];
बाह्य काष्ठा configfs_attribute *passthrough_pr_attrib_attrs[];

/* core helpers also used by command snooping in pscsi */
व्योम	*transport_kmap_data_sg(काष्ठा se_cmd *);
व्योम	transport_kunmap_data_sg(काष्ठा se_cmd *);
/* core helpers also used by xcopy during पूर्णांकernal command setup */
sense_reason_t	transport_generic_map_mem_to_cmd(काष्ठा se_cmd *,
		काष्ठा scatterlist *, u32, काष्ठा scatterlist *, u32);

bool	target_lun_is_rकरोnly(काष्ठा se_cmd *);
sense_reason_t passthrough_parse_cdb(काष्ठा se_cmd *cmd,
	sense_reason_t (*exec_cmd)(काष्ठा se_cmd *cmd));

bool target_sense_desc_क्रमmat(काष्ठा se_device *dev);
sector_t target_to_linux_sector(काष्ठा se_device *dev, sector_t lb);
bool target_configure_unmap_from_queue(काष्ठा se_dev_attrib *attrib,
				       काष्ठा request_queue *q);

अटल अंतरभूत bool target_dev_configured(काष्ठा se_device *se_dev)
अणु
	वापस !!(se_dev->dev_flags & DF_CONFIGURED);
पूर्ण

#पूर्ण_अगर /* TARGET_CORE_BACKEND_H */
