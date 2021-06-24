<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __mISDNdsp_H__
#घोषणा __mISDNdsp_H__

काष्ठा mISDN_dsp_element_arg अणु
	अक्षर	*name;
	अक्षर	*def;
	अक्षर	*desc;
पूर्ण;

काष्ठा mISDN_dsp_element अणु
	अक्षर	*name;
	व्योम	*(*new)(स्थिर अक्षर *arg);
	व्योम	(*मुक्त)(व्योम *p);
	व्योम	(*process_tx)(व्योम *p, अचिन्हित अक्षर *data, पूर्णांक len);
	व्योम	(*process_rx)(व्योम *p, अचिन्हित अक्षर *data, पूर्णांक len,
			अचिन्हित पूर्णांक txlen);
	पूर्णांक	num_args;
	काष्ठा mISDN_dsp_element_arg
		*args;
पूर्ण;

बाह्य पूर्णांक  mISDN_dsp_element_रेजिस्टर(काष्ठा mISDN_dsp_element *elem);
बाह्य व्योम mISDN_dsp_element_unरेजिस्टर(काष्ठा mISDN_dsp_element *elem);

काष्ठा dsp_features अणु
	पूर्णांक	hfc_id; /* unique id to identअगरy the chip (or -1) */
	पूर्णांक	hfc_dपंचांगf; /* set अगर HFCmulti card supports dपंचांगf */
	पूर्णांक	hfc_conf; /* set अगर HFCmulti card supports conferences */
	पूर्णांक	hfc_loops; /* set अगर card supports tone loops */
	पूर्णांक	hfc_echocanhw; /* set अगर card supports echocancelation*/
	पूर्णांक	pcm_id; /* unique id to identअगरy the pcm bus (or -1) */
	पूर्णांक	pcm_slots; /* number of slots on the pcm bus */
	पूर्णांक	pcm_banks; /* number of IO banks of pcm bus */
	पूर्णांक	unघड़ीed; /* data is not घड़ीed (has jitter/loss) */
	पूर्णांक	unordered; /* data is unordered (packets have index) */
पूर्ण;

#पूर्ण_अगर

