<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SEQ_खाता_NET_H__
#घोषणा __SEQ_खाता_NET_H__

#समावेश <linux/seq_file.h>

काष्ठा net;
बाह्य काष्ठा net init_net;

काष्ठा seq_net_निजी अणु
#अगर_घोषित CONFIG_NET_NS
	काष्ठा net *net;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा net *seq_file_net(काष्ठा seq_file *seq)
अणु
#अगर_घोषित CONFIG_NET_NS
	वापस ((काष्ठा seq_net_निजी *)seq->निजी)->net;
#अन्यथा
	वापस &init_net;
#पूर्ण_अगर
पूर्ण

/*
 * This one is needed क्रम proc_create_net_single since net is stored directly
 * in निजी not as a काष्ठा i.e. seq_file_net can't be used.
 */
अटल अंतरभूत काष्ठा net *seq_file_single_net(काष्ठा seq_file *seq)
अणु
#अगर_घोषित CONFIG_NET_NS
	वापस (काष्ठा net *)seq->निजी;
#अन्यथा
	वापस &init_net;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर
