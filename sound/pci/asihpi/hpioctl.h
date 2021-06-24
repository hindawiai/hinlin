<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


Linux HPI ioctl, and shared module init functions
*******************************************************************************/

पूर्णांक asihpi_adapter_probe(काष्ठा pci_dev *pci_dev,
			 स्थिर काष्ठा pci_device_id *pci_id);
व्योम asihpi_adapter_हटाओ(काष्ठा pci_dev *pci_dev);
व्योम __init asihpi_init(व्योम);
व्योम __निकास asihpi_निकास(व्योम);

पूर्णांक asihpi_hpi_release(काष्ठा file *file);

दीर्घ asihpi_hpi_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

/* This is called from hpअगरunc.c functions, called by ALSA
 * (or other kernel process) In this हाल there is no file descriptor
 * available क्रम the message cache code
 */
व्योम hpi_send_recv(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

#घोषणा HOWNER_KERNEL ((व्योम *)-1)
