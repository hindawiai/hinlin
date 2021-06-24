<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BSG_H
#घोषणा _LINUX_BSG_H

#समावेश <uapi/linux/bsg.h>

काष्ठा request;

#अगर_घोषित CONFIG_BLK_DEV_BSG
काष्ठा bsg_ops अणु
	पूर्णांक	(*check_proto)(काष्ठा sg_io_v4 *hdr);
	पूर्णांक	(*fill_hdr)(काष्ठा request *rq, काष्ठा sg_io_v4 *hdr,
				भ_शेषe_t mode);
	पूर्णांक	(*complete_rq)(काष्ठा request *rq, काष्ठा sg_io_v4 *hdr);
	व्योम	(*मुक्त_rq)(काष्ठा request *rq);
पूर्ण;

काष्ठा bsg_class_device अणु
	काष्ठा device *class_dev;
	पूर्णांक minor;
	काष्ठा request_queue *queue;
	स्थिर काष्ठा bsg_ops *ops;
पूर्ण;

पूर्णांक bsg_रेजिस्टर_queue(काष्ठा request_queue *q, काष्ठा device *parent,
		स्थिर अक्षर *name, स्थिर काष्ठा bsg_ops *ops);
पूर्णांक bsg_scsi_रेजिस्टर_queue(काष्ठा request_queue *q, काष्ठा device *parent);
व्योम bsg_unरेजिस्टर_queue(काष्ठा request_queue *q);
#अन्यथा
अटल अंतरभूत पूर्णांक bsg_scsi_रेजिस्टर_queue(काष्ठा request_queue *q,
		काष्ठा device *parent)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम bsg_unरेजिस्टर_queue(काष्ठा request_queue *q)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_BSG */
#पूर्ण_अगर /* _LINUX_BSG_H */
