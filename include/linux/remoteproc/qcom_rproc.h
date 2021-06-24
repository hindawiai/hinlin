<शैली गुरु>
#अगर_अघोषित __QCOM_RPROC_H__
#घोषणा __QCOM_RPROC_H__

काष्ठा notअगरier_block;

/**
 * क्रमागत qcom_ssr_notअगरy_type - Startup/Shutकरोwn events related to a remoteproc
 * processor.
 *
 * @QCOM_SSR_BEFORE_POWERUP:	Remoteproc about to start (prepare stage)
 * @QCOM_SSR_AFTER_POWERUP:	Remoteproc is running (start stage)
 * @QCOM_SSR_BEFORE_SHUTDOWN:	Remoteproc crashed or shutting करोwn (stop stage)
 * @QCOM_SSR_AFTER_SHUTDOWN:	Remoteproc is करोwn (unprepare stage)
 */
क्रमागत qcom_ssr_notअगरy_type अणु
	QCOM_SSR_BEFORE_POWERUP,
	QCOM_SSR_AFTER_POWERUP,
	QCOM_SSR_BEFORE_SHUTDOWN,
	QCOM_SSR_AFTER_SHUTDOWN,
पूर्ण;

काष्ठा qcom_ssr_notअगरy_data अणु
	स्थिर अक्षर *name;
	bool crashed;
पूर्ण;

#अगर IS_ENABLED(CONFIG_QCOM_RPROC_COMMON)

व्योम *qcom_रेजिस्टर_ssr_notअगरier(स्थिर अक्षर *name, काष्ठा notअगरier_block *nb);
पूर्णांक qcom_unरेजिस्टर_ssr_notअगरier(व्योम *notअगरy, काष्ठा notअगरier_block *nb);

#अन्यथा

अटल अंतरभूत व्योम *qcom_रेजिस्टर_ssr_notअगरier(स्थिर अक्षर *name,
					       काष्ठा notअगरier_block *nb)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक qcom_unरेजिस्टर_ssr_notअगरier(व्योम *notअगरy,
					       काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
