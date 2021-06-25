<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Microsoft Corporation.
 *
 * Author:  Jaskaran Singh Khurana <jaskarankhurana@linux.microsoft.com>
 *
 */
#अगर_अघोषित DM_VERITY_SIG_VERIFICATION_H
#घोषणा DM_VERITY_SIG_VERIFICATION_H

#घोषणा DM_VERITY_ROOT_HASH_VERIFICATION "DM Verity Sig Verification"
#घोषणा DM_VERITY_ROOT_HASH_VERIFICATION_OPT_SIG_KEY "root_hash_sig_key_desc"

काष्ठा dm_verity_sig_opts अणु
	अचिन्हित पूर्णांक sig_size;
	u8 *sig;
पूर्ण;

#अगर_घोषित CONFIG_DM_VERITY_VERIFY_ROOTHASH_SIG

#घोषणा DM_VERITY_ROOT_HASH_VERIFICATION_OPTS 2

पूर्णांक verity_verअगरy_root_hash(स्थिर व्योम *data, माप_प्रकार data_len,
			    स्थिर व्योम *sig_data, माप_प्रकार sig_len);
bool verity_verअगरy_is_sig_opt_arg(स्थिर अक्षर *arg_name);

पूर्णांक verity_verअगरy_sig_parse_opt_args(काष्ठा dm_arg_set *as, काष्ठा dm_verity *v,
				    काष्ठा dm_verity_sig_opts *sig_opts,
				    अचिन्हित पूर्णांक *argc, स्थिर अक्षर *arg_name);

व्योम verity_verअगरy_sig_opts_cleanup(काष्ठा dm_verity_sig_opts *sig_opts);

#अन्यथा

#घोषणा DM_VERITY_ROOT_HASH_VERIFICATION_OPTS 0

अटल अंतरभूत पूर्णांक verity_verअगरy_root_hash(स्थिर व्योम *data, माप_प्रकार data_len,
					  स्थिर व्योम *sig_data, माप_प्रकार sig_len)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool verity_verअगरy_is_sig_opt_arg(स्थिर अक्षर *arg_name)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक verity_verअगरy_sig_parse_opt_args(काष्ठा dm_arg_set *as,
			काष्ठा dm_verity *v, काष्ठा dm_verity_sig_opts *sig_opts,
			अचिन्हित पूर्णांक *argc, स्थिर अक्षर *arg_name)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम verity_verअगरy_sig_opts_cleanup(काष्ठा dm_verity_sig_opts *sig_opts)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DM_VERITY_VERIFY_ROOTHASH_SIG */
#पूर्ण_अगर /* DM_VERITY_SIG_VERIFICATION_H */
