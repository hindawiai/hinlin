<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2014 Intel Corporation

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#अगर IS_ENABLED(CONFIG_BT_DEBUGFS)

व्योम hci_debugfs_create_common(काष्ठा hci_dev *hdev);
व्योम hci_debugfs_create_bredr(काष्ठा hci_dev *hdev);
व्योम hci_debugfs_create_le(काष्ठा hci_dev *hdev);
व्योम hci_debugfs_create_conn(काष्ठा hci_conn *conn);

#अन्यथा

अटल अंतरभूत व्योम hci_debugfs_create_common(काष्ठा hci_dev *hdev)
अणु
पूर्ण

अटल अंतरभूत व्योम hci_debugfs_create_bredr(काष्ठा hci_dev *hdev)
अणु
पूर्ण

अटल अंतरभूत व्योम hci_debugfs_create_le(काष्ठा hci_dev *hdev)
अणु
पूर्ण

अटल अंतरभूत व्योम hci_debugfs_create_conn(काष्ठा hci_conn *conn)
अणु
पूर्ण

#पूर्ण_अगर
