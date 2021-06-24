<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIBATA_TRANSPORT_H
#घोषणा _LIBATA_TRANSPORT_H


बाह्य काष्ठा scsi_transport_ढाँचा *ata_scsi_transport_ढाँचा;

पूर्णांक ata_tlink_add(काष्ठा ata_link *link);
व्योम ata_tlink_delete(काष्ठा ata_link *link);

पूर्णांक ata_tport_add(काष्ठा device *parent, काष्ठा ata_port *ap);
व्योम ata_tport_delete(काष्ठा ata_port *ap);

काष्ठा scsi_transport_ढाँचा *ata_attach_transport(व्योम);
व्योम ata_release_transport(काष्ठा scsi_transport_ढाँचा *t);

__init पूर्णांक libata_transport_init(व्योम);
व्योम __निकास libata_transport_निकास(व्योम);
#पूर्ण_अगर
