<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_INET_DATALINK_H_
#घोषणा _NET_INET_DATALINK_H_

काष्ठा datalink_proto अणु
        अचिन्हित अक्षर   type[8];

	काष्ठा llc_sap   *sap;

        अचिन्हित लघु  header_length;

        पूर्णांक     (*rcvfunc)(काष्ठा sk_buff *, काष्ठा net_device *,
                                काष्ठा packet_type *, काष्ठा net_device *);
	पूर्णांक     (*request)(काष्ठा datalink_proto *, काष्ठा sk_buff *,
                                        अचिन्हित अक्षर *);
	काष्ठा list_head node;
पूर्ण;

काष्ठा datalink_proto *make_EII_client(व्योम);
व्योम destroy_EII_client(काष्ठा datalink_proto *dl);
#पूर्ण_अगर
