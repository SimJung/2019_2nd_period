int p(int semid) {
    struct sembuf p_buf;
    p_buf.sem_num = 0;
    p_buf.sem_op = -1;
    p_buf.sem_flg = SEM_UNDO;

    if( semop(semid, &p_buf, 1) == -1){
        perror("p(semid) failed");
        exit(1);
    }

    return 0;
}

int v (int semid) {
    struct sembuf v_buf;
    v_buf.sem_num = 0;
    v_buf.sem_op = 1;
    v_buf.sem_flg = SEM_UNDO;

    if( semop(semid, &v_buf, 1) == -1){
        perror("v(semid) failed");
        exit(1);
    }

    return 0;
}

int p(int sem){
    while(sem == 0) wait();
    sem --;
}

int v(int sem){
    sem++;
    if(!queue.empty())
        start q.front();
}

int p(int semid){
    struct sembuf p_buf;
    p_buf.sem_num = 0;
    p_buf.sem_op = -1;
    p_buf.sem_flg = SEM_UNDO;

    semop(semid, &p_buf, 1);
}

int v(int semid){
    struct sembuf v_buf;
    v_buf.sem_num = 0;
    v_buf.sem_op = -1;
    v_buf.sem_flg = SEM_UNDO;

    semop(semid, &v_buf, 1);
}

int initsem(key_t semkey) {
	union semun semunarg;
	int status;
	int semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0600);
	
	semunarg.val = 1;
	status = semctl(semid, 0, SETVAL, semunarg);

	return semid;
}

int initsem2(key_t semkey) {
	union semun semunarg;
	int status;
	int semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0600);

	semunarg.val = 1;
	status = semctl(semid, 0, SETVAL, semunarg);
	return semid;
}
