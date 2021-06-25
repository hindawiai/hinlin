<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_KMS_HANDLES_H__
#घोषणा __NV50_KMS_HANDLES_H__

/*
 * Various hard-coded object handles that nouveau uses. These are made-up by
 * nouveau developers, not Nvidia. The only signअगरicance of the handles chosen
 * is that they must all be unique.
 */
#घोषणा NV50_DISP_HANDLE_SYNCBUF                                        0xf0000000
#घोषणा NV50_DISP_HANDLE_VRAM                                           0xf0000001

#घोषणा NV50_DISP_HANDLE_WNDW_CTX(kind)                        (0xfb000000 | kind)
#घोषणा NV50_DISP_HANDLE_CRC_CTX(head, i) (0xfc000000 | head->base.index << 1 | i)

#पूर्ण_अगर /* !__NV50_KMS_HANDLES_H__ */
