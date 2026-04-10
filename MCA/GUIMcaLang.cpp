#include <sstream>
#include <vector>

#include "GUIMcaLang.h"
#include "helpers.h"

CGUIMcaLang::CGUIMcaLang(void)
{
	for (std::map<const std::string, const std::string>::const_iterator i = m_default_lang.begin(); i != m_default_lang.end(); i++)
	{
		m_curr_lang.insert(*i);
	}
}

void CGUIMcaLang::trimLeft(std::string& str, const char* chars2remove)
{
	if (!str.empty())
	{
		std::string::size_type pos = str.find_first_not_of(chars2remove);

		if (pos != std::string::npos)
			str.erase(0,pos);
		else
			str.erase( str.begin() , str.end() );
	}
}

void CGUIMcaLang::trimRight(std::string& str, const char* chars2remove)
{
	if (!str.empty())
	{
		std::string::size_type pos = str.find_last_not_of(chars2remove);

		if (pos != std::string::npos)
			str.erase(pos+1);
		else
			str.erase( str.begin() , str.end() );
	}
}

void CGUIMcaLang::initLang(std::string input)
{
	replace(&input, "\r\n", "\n");
	replace(&input, "\r", "\n");
	std::istringstream instream(input);
	std::string line;
	std::vector<std::string> all_lines;

	while(std::getline(instream, line, '\n'))
	{
		trimLeft(line, " ");
		trimRight(line, " ");
		if (line.empty()) continue;
		if (line[0] == '#' || (line[0] == '/' && line[1] == '/')) continue;
		if (line.find("=") == std::string::npos) continue;

		all_lines.push_back(line);
	}

	std::string::size_type subpos;
	std::string::size_type laspos;
	for (std::map<const std::string, const std::string>::const_iterator i = m_default_lang.begin(); i != m_default_lang.end(); i++)
	{
		for (u32 li = 0; li < all_lines.size(); li++)
		{
			subpos = all_lines[li].find((*i).first);
			if (subpos != std::string::npos)
			{
				if (all_lines[li][subpos+(*i).first.length()] == ' ' || all_lines[li][subpos+(*i).first.length()] == '=')
				{
					subpos = all_lines[li].find("\"");
					laspos = all_lines[li].rfind("\"");
					if (subpos != laspos)
					{
						m_curr_lang[(*i).first] = all_lines[li].substr(subpos+1, (laspos)-(subpos+1));
						replace(&m_curr_lang[(*i).first], "\\\"", "\"");
						replace(&m_curr_lang[(*i).first], "\\n", "\n");
					}
				}
			}
		}
	}

	all_lines.clear();
}

CGUIMcaLang::~CGUIMcaLang(void)
{
	m_curr_lang.clear();
}

const char *CGUIMcaLang::getText(const char *label)
{
	return m_curr_lang[label].c_str();
}

void CGUIMcaLang::replace(std::string *base, const std::string find, const std::string repl)
{
	int lenrepl = repl.length();
	int lenfind = find.length();

	u32 i = 0;
	while ( std::string::npos != (i = base->find(find, i)) )
	{
		base->replace( i, lenfind, repl);
		i += lenrepl;
	}
}

void CGUIMcaLang::replace(std::string *base, const std::string find, const long long repln)
{
	std::ostringstream conv;

	conv << repln;
	std::string repl = conv.str();

	int lenrepl = repl.length();
	int lenfind = find.length();

	u32 i = 0;
	while ( std::string::npos != (i = base->find(find, i)) )
	{
		base->replace( i, lenfind, repl);
		i += lenrepl;
	}
}

const CGUIMcaLang::langmapRaw CGUIMcaLang::m_default_lang_raw[] = {
   CGUIMcaLang::langmapRaw("LNG_MWND_CHOOSE_SLOT", "Selecione o slot"),
   CGUIMcaLang::langmapRaw("LNG_OPER_PS2_MEMORY_CARD", "PS2 Memory Card"),
   CGUIMcaLang::langmapRaw("LNG_OPER_PSX_MEMORY_CARD", "PS1 Memory Card"),
   CGUIMcaLang::langmapRaw("LNG_OPER_FORMAT", "Formatar"),
   CGUIMcaLang::langmapRaw("LNG_OPER_UNFORMAT", "Desformatar"),
   CGUIMcaLang::langmapRaw("LNG_OPER_MAKE_IMAGE", "Criar imagem do MC"),
   CGUIMcaLang::langmapRaw("LNG_OPER_RESTORE_IMAGE", "Restaurar imagem do MC"),
   CGUIMcaLang::langmapRaw("LNG_OPER_INFO", "Informacoes do MC"),
   CGUIMcaLang::langmapRaw("LNG_OPER_FAST", "Rapido"),
   CGUIMcaLang::langmapRaw("LNG_OPER_FULL", "Completo"),
   CGUIMcaLang::langmapRaw("LNG_OPER_CHOOSE_MC_SIZE", "\nSelecione o tamanho do seu MC"),
   CGUIMcaLang::langmapRaw("LNG_OPER_MEGABYTE", "{CARDSIZE} MB"),
   CGUIMcaLang::langmapRaw("LNG_OPER_YES", "Sim"),
   CGUIMcaLang::langmapRaw("LNG_OPER_NO", "Nao"),
   CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_FORMAT_DATA_LOST", "Voce tem certeza de que quer formatar o MC?\n\nFormatar ira apagar todos os dados do MC!"),
   CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_UNFORMAT_DATA_LOST", "Voce tem certeza de que quer desformatar o MC?\n\nDesformatar ira apagar todos os dados do MC!"),
   CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_RESTORE_DATA_LOST", "Voce tem certeza de que quer restaurar a imagem do MC?\n\nRestaurar a imagem ira apagar todos os dados do MC!"),
   CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_OVERWRITE", "O arquivo selecionado ja existe, tem certeza que quer sobrescreve-lo?\n\nSobrecrever ira fazer com que todos dados sejam perdidos."),
   CGUIMcaLang::langmapRaw("LNG_WARN_CAP", "Aviso..."),
   CGUIMcaLang::langmapRaw("LNG_WARN_NO_CARD_IN_SLOT", "O Memory Card no Slot {SLOTNUM} foi removido ou alterado. O programa ira retornar para o menu principal.\n\n\nPressione X para continuar."),
   CGUIMcaLang::langmapRaw("LNG_PROGRESS_DO_NOT_REMOVE", "\nNao remova o Memory Card, nao resete ou desligue o console"),
   CGUIMcaLang::langmapRaw("LNG_PROGRESS_SUCCESS", "\nA operacao foi concluida com sucesso\nPressione X para continuar."),
   CGUIMcaLang::langmapRaw("LNG_PROGRESS_FAIL", "\nA operacao falhou\nPressione X para continuar."),
   CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_READ", "Selecione o arquivo para carregar"),
   CGUIMcaLang::langmapRaw("LNG_FILE_CHOOSE_FILE_SAVE", "Selecione o arquivo para salvar"),
   CGUIMcaLang::langmapRaw("LNG_INFO_CAPTION", "Informacoes do MC"),
   CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_MB", "MB"),
   CGUIMcaLang::langmapRaw("LNG_INFO_UNIT_KB", "KB"),
   CGUIMcaLang::langmapRaw("LNG_INFO_MC_PSX", "PS1"),
   CGUIMcaLang::langmapRaw("LNG_INFO_MC_PS2", "PS2"),
   CGUIMcaLang::langmapRaw("LNG_INFO_SLOT", "Memory card slot:"),
   CGUIMcaLang::langmapRaw("LNG_INFO_TYPE", "Tipo de cartao:"),
   CGUIMcaLang::langmapRaw("LNG_INFO_PAGESIZE", "Tamanho de pagina:"),
   CGUIMcaLang::langmapRaw("LNG_INFO_PAGESINBLOCK", "Paginas por bloco:"),
   CGUIMcaLang::langmapRaw("LNG_INFO_PAGESTOTAL", "Total de paginas:"),
   CGUIMcaLang::langmapRaw("LNG_INFO_THX_TXT", "\nA Sony pelo console que nos entreteu durante longas tardes, que nos manteve acordados durante incontaveis noites e que fez nossas namoradas terminarem conosco ;).\n\nAo PiotrB por ter tirado a foto do memory card do PS1 e a todos que estiveram envolvidos em sua sessao de fotos."),
   CGUIMcaLang::langmapRaw("LNG_INFO_THX_CAP", "Agradecimentos:"),
   CGUIMcaLang::langmapRaw("LNG_TIP_VKBD_MASK", "START - criar novo arquivo\nL2/R2 - Ativar/desativar filtro de arquivo"),
   CGUIMcaLang::langmapRaw("LNG_TIP_MASK_ENABLED", "Filtro de arquivo ativado"),
   CGUIMcaLang::langmapRaw("LNG_TIP_MASK_DISABLED", "Filtro de arquivo desativado"),
   CGUIMcaLang::langmapRaw("LNG_VKBD_WARN_WRONG_NAME", "O nome de arquivo especificado contem caracteres invalidos. Altere o nome do arquivo para continuar.\n\n\nPressione qualquer botao para continuar."),
   CGUIMcaLang::langmapRaw("LNG_EXIT_SELECT_ELF", "\n\nSelecione um arquivo para executar..."),
   CGUIMcaLang::langmapRaw("LNG_EXIT_INVALID", "\n\nO arquivo selecionado nao e um executavel ELF."),
   CGUIMcaLang::langmapRaw("LNG_EXIT_FAILED", "\n\nO arquivo selecionado nao pode ser aberto."),
   CGUIMcaLang::langmapRaw("LNG_OPER_QUESTION_SIZE_MISMATCH", "Voce selecionou um tamanho maior que o padrao. Isso pode danificar o seu memory card!\n\nVoce quer continuar?"),
};
const int CGUIMcaLang::m_numof_entries = countof(CGUIMcaLang::m_default_lang_raw);
const std::map<const std::string, const std::string> CGUIMcaLang::m_default_lang(CGUIMcaLang::m_default_lang_raw, CGUIMcaLang::m_default_lang_raw + CGUIMcaLang::m_numof_entries);
