<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43legacy_DEBUGFS_H_
#घोषणा B43legacy_DEBUGFS_H_

काष्ठा b43legacy_wldev;
काष्ठा b43legacy_txstatus;

क्रमागत b43legacy_dyndbg अणु /* Dynamic debugging features */
	B43legacy_DBG_XMITPOWER,
	B43legacy_DBG_DMAOVERFLOW,
	B43legacy_DBG_DMAVERBOSE,
	B43legacy_DBG_PWORK_FAST,
	B43legacy_DBG_PWORK_STOP,
	__B43legacy_NR_DYNDBG,
पूर्ण;


#अगर_घोषित CONFIG_B43LEGACY_DEBUG

काष्ठा dentry;

#घोषणा B43legacy_NR_LOGGED_TXSTATUS	100

काष्ठा b43legacy_txstatus_log अणु
	काष्ठा b43legacy_txstatus *log;
	पूर्णांक end;
	spinlock_t lock;	/* lock क्रम debugging */
पूर्ण;

काष्ठा b43legacy_dfs_file अणु
	काष्ठा dentry *dentry;
	अक्षर *buffer;
	माप_प्रकार data_len;
पूर्ण;

काष्ठा b43legacy_dfsentry अणु
	काष्ठा b43legacy_wldev *dev;
	काष्ठा dentry *subdir;

	काष्ठा b43legacy_dfs_file file_tsf;
	काष्ठा b43legacy_dfs_file file_ucode_regs;
	काष्ठा b43legacy_dfs_file file_shm;
	काष्ठा b43legacy_dfs_file file_txstat;
	काष्ठा b43legacy_dfs_file file_txघातer_g;
	काष्ठा b43legacy_dfs_file file_restart;
	काष्ठा b43legacy_dfs_file file_loctls;

	काष्ठा b43legacy_txstatus_log txstatlog;

	/* Enabled/Disabled list क्रम the dynamic debugging features. */
	bool dyn_debug[__B43legacy_NR_DYNDBG];
	/* Dentries क्रम the dynamic debugging entries. */
	काष्ठा dentry *dyn_debug_dentries[__B43legacy_NR_DYNDBG];
पूर्ण;

पूर्णांक b43legacy_debug(काष्ठा b43legacy_wldev *dev,
		    क्रमागत b43legacy_dyndbg feature);

व्योम b43legacy_debugfs_init(व्योम);
व्योम b43legacy_debugfs_निकास(व्योम);
व्योम b43legacy_debugfs_add_device(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_debugfs_हटाओ_device(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_debugfs_log_txstat(काष्ठा b43legacy_wldev *dev,
				  स्थिर काष्ठा b43legacy_txstatus *status);

#अन्यथा /* CONFIG_B43LEGACY_DEBUG*/

अटल अंतरभूत
पूर्णांक b43legacy_debug(काष्ठा b43legacy_wldev *dev,
		    क्रमागत b43legacy_dyndbg feature)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम b43legacy_debugfs_init(व्योम) अणु पूर्ण
अटल अंतरभूत
व्योम b43legacy_debugfs_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत
व्योम b43legacy_debugfs_add_device(काष्ठा b43legacy_wldev *dev) अणु पूर्ण
अटल अंतरभूत
व्योम b43legacy_debugfs_हटाओ_device(काष्ठा b43legacy_wldev *dev) अणु पूर्ण
अटल अंतरभूत
व्योम b43legacy_debugfs_log_txstat(काष्ठा b43legacy_wldev *dev,
				  स्थिर काष्ठा b43legacy_txstatus *status)
				  अणु पूर्ण

#पूर्ण_अगर /* CONFIG_B43LEGACY_DEBUG*/

#पूर्ण_अगर /* B43legacy_DEBUGFS_H_ */
