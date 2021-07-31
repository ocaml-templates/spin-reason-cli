open Cmdliner;

let cmds = [Cmd_hello.cmd];

/* Command line interface */

let doc = "A short, but powerful statement about your project";

let sdocs = Manpage.s_common_options;

let exits = Common.exits;

let envs = Common.envs;

let man = [
  `S(Manpage.s_description),
  `P("A short, but powerful statement about your project"),
  `S(Manpage.s_commands),
  `S(Manpage.s_common_options),
  `S(Manpage.s_exit_status),
  `P("These environment variables affect the execution of $(mname):"),
  `S(Manpage.s_environment),
  `S(Manpage.s_bugs),
  `P("File bug reports at $(i,%%PKG_ISSUES%%)"),
  `S(Manpage.s_authors),
  `P("Thibaut Mattio, $(i,https://github.com/tmattio)"),
];

let default_cmd = {
  let term =
    Common.Syntax.(
      Term.ret @@
      {
        let+ _ = Common.term;
        `Help((`Pager, None));
      }
    );

  let info =
    Term.info(
      "demo",
      ~version="%%VERSION%%",
      ~doc,
      ~sdocs,
      ~exits,
      ~man,
      ~envs,
    );
  (term, info);
};

let () = Term.(exit_status @@ eval_choice(default_cmd, cmds));
