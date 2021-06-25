<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PTP PCH
 *
 * Copyright 2019 Linaro Ltd.
 *
 * Author Lee Jones <lee.jones@linaro.org>
 */

#अगर_अघोषित _PTP_PCH_H_
#घोषणा _PTP_PCH_H_

व्योम pch_ch_control_ग_लिखो(काष्ठा pci_dev *pdev, u32 val);
u32  pch_ch_event_पढ़ो(काष्ठा pci_dev *pdev);
व्योम pch_ch_event_ग_लिखो(काष्ठा pci_dev *pdev, u32 val);
u32  pch_src_uuid_lo_पढ़ो(काष्ठा pci_dev *pdev);
u32  pch_src_uuid_hi_पढ़ो(काष्ठा pci_dev *pdev);
u64  pch_rx_snap_पढ़ो(काष्ठा pci_dev *pdev);
u64  pch_tx_snap_पढ़ो(काष्ठा pci_dev *pdev);
पूर्णांक  pch_set_station_address(u8 *addr, काष्ठा pci_dev *pdev);

#पूर्ण_अगर /* _PTP_PCH_H_ */
