# pipex

## 1️⃣ 프로젝트 소개

Pipex는 리눅스 파이프(|) 기능을 직접 구현하는 프로젝트입니다. 셸에서 cmd1 | cmd2 같은 명령어 체인이 동작하는 원리를 깊이 이해하고, 저수준 시스템 콜을 통해 프로세스 간 통신(IPC, Inter-Process Communication) 을 직접 구현하는 것이 목적입니다. 보너스 파트에서는 여러 개의 명령어를 파이프라인으로 연결하거나 heredoc 기능까지 다룹니다.

---

## 2️⃣ 과제 목표
	•	파이프, 프로세스, 파일 디스크립터, 시스템 콜을 실제로 다뤄 리눅스 파이프라인의 내부 동작 원리를 학습.
	•	부모/자식 프로세스 간의 실행 흐름을 제어하고, 표준 입출력을 리다이렉션하는 기법 습득.
	•	보너스 구현을 통해 다중 파이프라인 및 heredoc을 지원하도록 확장.

---

## 3️⃣ 구현 사항
* 기본 파트
  - ./pipex file1 cmd1 cmd2 file2 형식의 실행 파일 구현.
  - file1의 내용을 cmd1으로 실행 → 출력 결과를 cmd2의 입력으로 전달 → 최종 결과를 file2에 저장.
  - 내부적으로는 pipe(), fork(), dup2(), execve() 등의 시스템 콜을 조합하여 동작.
* 보너스 파트
  - 다중 명령어 지원: ./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2 형태로 여러 명령어를 순차적으로 연결.
  - Heredoc 기능: ./pipex here_doc LIMITER cmd1 cmd2 file
    - 표준 입력에서 LIMITER 문자열이 나올 때까지 입력을 받아 파이프라인의 첫 번째 명령어로 전달.
  - PATH 탐색 기능: 실행 가능한 명령어를 환경 변수 PATH에서 탐색.
  - 에러 처리 강화: 잘못된 파일 디스크립터, 잘못된 명령어, 권한 문제 등에 대한 robust한 에러 핸들링.

---

## 4️⃣ 배운 점
	•	시스템 프로그래밍: fork, execve, pipe, dup2, waitpid 같은 저수준 시스템 콜의 실제 동작과 쓰임새.
	•	파일 디스크립터 관리: 프로세스 실행 중 열린 파일과 파이프의 적절한 닫기/복제를 통한 자원 누수 방지.
	•	프로세스 제어 흐름: 부모-자식 간 역할 분담, exit code 처리.
	•	확장성: 단일 파이프에서 시작해 다중 파이프 및 heredoc으로 확장하는 과정에서 모듈화된 코드 설계 중요성을 체득.
	•	실무 감각: 실제 셸의 파이프 동작 원리를 재현하며 리눅스 환경의 기초 원리를 몸소 익힘.

---

## 5️⃣ 사용 방법
### 기본 실행
bash
```
./pipex infile "ls -l" "wc -l" outfile
```
동작 = < infile ls -l | wc -l > outfile

### 보너스: 다중 명령어
bash
```
./pipex infile "grep a1" "sort" "uniq" outfile
```
동작 = < infile grep a1 | sort | uniq > outfile

### 보너스: heredoc
bash
```
./pipex here_doc END "cat" "wc -l" outfile
```
표준 입력에서 END가 입력될 때까지의 내용을 cat | wc -l로 처리 후 outfile에 저장.

---

## 6️⃣ 동작 영상
	•	./pipex infile1 "cat" "wc -l" outfile
	•	./pipex infile1 "grep test" "sort" outfile
	•	./pipex infile2 "sort" "uniq" outfile
	•	./pipex infile3 "sort" "cat -e" outfile
	•	./pipex emptyfile "cat" "wc -l" outfile
	•	./pipex infile4 "wc -c" "cat" outfile

https://github.com/user-attachments/assets/4c75f968-537e-439b-949f-320cceeb6e2e

	•	./pipex nofile "ls" "wc -l" outfile
	•	./pipex infile "nosuchcommand" "wc -l" outfile
	•	./pipex infile "cat" "grep a" "wc -l" outfile
	•	./pipex infile "tr a-z A-Z" "sort" "uniq" "wc -l" outfile
	•	./pipex here_doc LIMITER "cat" "wc -l" outfile
	•	chmod 444 outfile && ./pipex infile "cat" "wc -l" outfile
	•	./pipex infile "sleep 2" "echo done" outfile

https://github.com/user-attachments/assets/3751a360-ae0b-4ef9-96ea-69210b7fb6e3


---

## 7️⃣ 기술 스택
	•	언어: C
	•	환경: Unix/Linux
	•	주요 시스템 콜: open, close, pipe, fork, dup2, execve, wait, perror
	•	빌드 도구: GNU Make
